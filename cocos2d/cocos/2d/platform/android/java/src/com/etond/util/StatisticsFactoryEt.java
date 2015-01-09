package com.etond.util;

import android.content.Context;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.content.pm.PackageManager.NameNotFoundException;

public class StatisticsFactoryEt
{
	public static StatisticsImpEt create(Context cxt)
	{
		try 
		{
			ApplicationInfo appInfo;
			appInfo = cxt.getPackageManager().getApplicationInfo(cxt.getPackageName(),PackageManager.GET_META_DATA);
			String msg=appInfo.metaData.getString("Statistics");

			if(msg == "umeng")
			{
				return new UMStatisticsEt();
			}
			
		} catch (NameNotFoundException e) 
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return new UMStatisticsEt();
	}
	
}
