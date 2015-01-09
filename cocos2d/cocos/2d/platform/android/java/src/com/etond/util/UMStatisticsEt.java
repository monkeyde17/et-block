package com.etond.util;


import com.umeng.analytics.game.UMGameAgent;


import android.content.Context;

public class UMStatisticsEt implements StatisticsImpEt 
{
	public static Context m_cxt = null;

	@Override
	public void init(Context cxt, boolean debug) 
	{
		// TODO Auto-generated method stub
		m_cxt = cxt;
		UMGameAgent.init(m_cxt);
		UMGameAgent.setDebugMode(debug);
	}

	@Override
	public void pause() 
	{
		// TODO Auto-generated method stub
		UMGameAgent.onPause(m_cxt);
		
	}

	@Override
	public void resume()
	{
		// TODO Auto-generated method stub
		UMGameAgent.onResume(m_cxt);
	}

	@Override
	public void destory()
	{
		// TODO Auto-generated method stub
	}



	@Override
	public void Statistics(int idx, String evt_id) 
	{
		// TODO Auto-generated method stub
		
	}
}
