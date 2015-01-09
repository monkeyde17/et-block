package com.etond.util;

import android.content.Context;


public class StatisticsEt 
{
	private static Context 			m_cxt = null;
	private static StatisticsImpEt	m_statisticsImp = null;
	private static boolean 			m_debug = false;
	
	public static void init(Context cxt, boolean debug)
	{
		m_cxt = cxt;
		m_debug = debug;
		
		m_statisticsImp = StatisticsFactoryEt.create(m_cxt);
		m_statisticsImp.init(m_cxt, m_debug);
	}
	
	
	public static void statistics(int idx, String evt_id)
	{
		m_statisticsImp.Statistics(idx, evt_id);
	}
	
	
	public static void onPause()
	{
		m_statisticsImp.pause();
	}
	
	
	public static void onResume()
	{
		m_statisticsImp.resume();
	}
	
	public static void onDestory()
	{
		m_statisticsImp.destory();
	}
}
