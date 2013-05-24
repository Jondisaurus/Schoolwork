package com.example.animalfun;

import java.io.IOException;

import android.content.Context;
import android.media.MediaPlayer;

public class AndroidTools 
{
	private static MediaPlayer mediaPlayer = null;
	
	public static void PlaySound(Context context, int resId)
	{
		if (mediaPlayer != null)
		{
			mediaPlayer.release();
		}
		
		mediaPlayer = MediaPlayer.create(context, resId);					
        mediaPlayer.start();        
	}
	
	public static void wait(int milliseconds)
	{	
		try 
		{
			Thread.sleep(milliseconds);
		} catch (InterruptedException e) 
		{
		}
	}
}
