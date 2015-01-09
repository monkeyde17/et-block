package com.etond.util;


import android.content.Context;

public interface StatisticsImpEt 
{
	public void init(Context cxt, boolean debug);
	public void pause();
	public void resume();
	public void destory();
	public void Statistics(int idx, String evt_id);
}
