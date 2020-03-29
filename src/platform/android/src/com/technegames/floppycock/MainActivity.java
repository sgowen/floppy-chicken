package com.technegames.floppycock;

import android.annotation.SuppressLint;
import android.graphics.Point;
import android.media.AudioManager;
import android.opengl.GLSurfaceView;
import android.os.Build;
import android.os.Build.VERSION;
import android.os.Bundle;
import android.util.Log;
import android.view.Display;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnTouchListener;
import android.view.WindowManager;
import android.widget.LinearLayout;
import android.widget.Toast;

import com.google.example.games.basegameutils.BaseGameActivity;
import com.technegames.floppycock.R;

public final class MainActivity extends BaseGameActivity
{
	private RendererWrapper rendererWrapper;
	private GLSurfaceView glSurfaceView;
	boolean isAttemptingToSubmitAndOrViewLeaderboard = false;

	@Override
	protected void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);

		setContentView(R.layout.activity_main);

		Point size = getScreenSize();

		Log.d("Floppy Chicken", "dimension " + size.x + " x " + size.y);

		rendererWrapper = new RendererWrapper(this, size.x, size.y);
		glSurfaceView = new GLSurfaceView(this);
		glSurfaceView.setEGLContextClientVersion(1);
		glSurfaceView.setRenderer(rendererWrapper);

		LinearLayout gameContainer = (LinearLayout) findViewById(R.id.game);
		gameContainer.addView(glSurfaceView);

		getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
		getWindow().addFlags(WindowManager.LayoutParams.FLAG_SHOW_WHEN_LOCKED);
		setVolumeControlStream(AudioManager.STREAM_MUSIC);

		glSurfaceView.setOnTouchListener(new OnTouchListener()
		{
			@Override
			public boolean onTouch(View v, final MotionEvent event)
			{
				if (event != null)
				{
					if (event.getAction() == MotionEvent.ACTION_DOWN)
					{
						glSurfaceView.queueEvent(new Runnable()
						{
							@Override
							public void run()
							{
								rendererWrapper.handleTouchDown(event.getX(), event.getY());
							}
						});
					}
					else if (event.getAction() == MotionEvent.ACTION_MOVE)
					{
						glSurfaceView.queueEvent(new Runnable()
						{
							@Override
							public void run()
							{
								rendererWrapper.handleTouchDragged(event.getX(), event.getY());
							}
						});
					}
					else if (event.getAction() == MotionEvent.ACTION_UP)
					{
						glSurfaceView.queueEvent(new Runnable()
						{
							@Override
							public void run()
							{
								rendererWrapper.handleTouchUp(event.getX(), event.getY());
							}
						});
					}

					return true;
				}
				else
				{
					return false;
				}
			}
		});
	}

	@Override
	protected void onResume()
	{
		super.onResume();

		glSurfaceView.onResume();
		rendererWrapper.onResume();
	}

	@Override
	protected void onPause()
	{
		super.onPause();

		rendererWrapper.onPause(isFinishing());
		glSurfaceView.onPause();
	}

	@Override
	public void onBackPressed()
	{
		if (rendererWrapper.handleOnBackPressed())
		{
			return;
		}

		super.onBackPressed();
	}

	@Override
	public void onSignInFailed()
	{
		if (isAttemptingToSubmitAndOrViewLeaderboard)
		{
			isAttemptingToSubmitAndOrViewLeaderboard = false;
			Toast.makeText(this, R.string.sign_in_failed, Toast.LENGTH_SHORT).show();
		}
	}

	@Override
	public void onSignInSucceeded()
	{
		if (isAttemptingToSubmitAndOrViewLeaderboard)
		{
			isAttemptingToSubmitAndOrViewLeaderboard = false;
			submitBestScoreToLeaderboard();
		}
	}

	public final void submitBestScoreToLeaderboard()
	{
		runOnUiThread(new Runnable()
		{
			@Override
			public void run()
			{
				if (isSignedIn())
				{
					long score = AppPrefs.getInstance(MainActivity.this).getBestScore();
					getGamesClient().submitScore(getString(R.string.leaderboard_floppy_chicken), score);
					startActivityForResult(getGamesClient().getLeaderboardIntent(getString(R.string.leaderboard_floppy_chicken)), 1337);
				}
				else
				{
					isAttemptingToSubmitAndOrViewLeaderboard = true;
					beginUserInitiatedSignIn();
				}
			}
		});
	}

	@SuppressLint("NewApi")
	@SuppressWarnings("deprecation")
	private Point getScreenSize()
	{
		Display display = getWindowManager().getDefaultDisplay();
		Point size = new Point();

		if (VERSION.SDK_INT >= Build.VERSION_CODES.HONEYCOMB_MR2)
		{
			display.getSize(size);
		}
		else
		{
			size.x = display.getWidth();
			size.y = display.getHeight();
		}

		return size;
	}
}