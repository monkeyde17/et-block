package org.cocos2dx.weibo;

import java.io.File;

import android.os.Environment;

public class FilePath {
	static public String getScreenShotPath()
	{
		if (Environment.getExternalStorageState().equals(android.os.Environment.MEDIA_MOUNTED))
		{
			File newFile = new File(Environment.getExternalStorageDirectory() + "/" + "NoWhiteCatScreenShot");
			if (!newFile.exists())
			{
				newFile.mkdirs();
			}
			return newFile.toString();
		}
		return null;
	}

}
