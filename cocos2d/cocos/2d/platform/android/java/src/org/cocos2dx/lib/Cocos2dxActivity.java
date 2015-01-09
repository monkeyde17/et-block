/****************************************************************************
Copyright (c) 2010-2013 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
 ****************************************************************************/
package org.cocos2dx.lib;

import org.cocos2dx.lib.Cocos2dxHelper.Cocos2dxHelperListener;

import com.etond.util.StatisticsEt;
import com.renn.sharecomponent.MessageTarget;
import com.renn.sharecomponent.RennShareComponent;
import com.renn.sharecomponent.RennShareComponent.SendMessageListener;
import com.renn.sharecomponent.ShareMessageError;
import com.renn.sharecomponent.message.RennImgTextMessage;
import com.tencent.mm.sdk.openapi.IWXAPI;
import com.tencent.mm.sdk.openapi.SendMessageToWX;
import com.tencent.mm.sdk.openapi.WXAPIFactory;
import com.tencent.mm.sdk.openapi.WXImageObject;
import com.tencent.mm.sdk.openapi.WXMediaMessage;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.os.Message;
import android.view.ViewGroup;
import android.text.StaticLayout;
import android.util.Log;
import android.widget.FrameLayout;

public abstract class Cocos2dxActivity extends Activity implements
		Cocos2dxHelperListener {
	// ===========================================================
	// Constants
	// ===========================================================

	private static final String TAG = Cocos2dxActivity.class.getSimpleName();

	// ===========================================================
	// Fields
	// ===========================================================

	private Cocos2dxGLSurfaceView mGLSurfaceView;
	private static Cocos2dxHandler mHandler;
	private static Context sContext = null;
	private static Cocos2dxActivity mActivity = null;

	public static Context getContext() {
		return sContext;
	}

	// renren
	private static RennShareComponent shareComponent;

	private static final String RENREN_APP_ID = "269674";// "237274";

	private static final String RENREN_API_KEY = "20b5547c67d34de2bf328b5f47fa2767";

	private static final String RENREN_SECRET_KEY = "6d267f3e9b1d4862a93080a274473461";

	// weixin
	private static final String WEIXIN_APP_ID = "wxe9cd70f69dafad0a";

	private static IWXAPI api;

	// ===========================================================
	// Constructors
	// ===========================================================

	@Override
	protected void onCreate(final Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		try {
			ApplicationInfo ai = getPackageManager().getApplicationInfo(
					getPackageName(), PackageManager.GET_META_DATA);
			Bundle bundle = ai.metaData;
			try {
				String libName = bundle.getString("android.app.lib_name");
				System.loadLibrary(libName);
			} catch (Exception e) {
				// ERROR
			}
		} catch (PackageManager.NameNotFoundException e) {
			// ERROR
		}
		mActivity = this;
		sContext = this;
		this.mHandler = new Cocos2dxHandler(this);

		//this.addContentddView(view, params)
		initRenren();
    	initWeixin();
    	
		this.init();

		StatisticsEt.init(this, false);
		
		Cocos2dxHelper.init(this);
	}
	void initRenren()
	{
		shareComponent = RennShareComponent.getInstance(this);
		shareComponent.init(RENREN_APP_ID, RENREN_API_KEY, RENREN_SECRET_KEY);
		
		shareComponent.setSendMessageListener(
				new SendMessageListener() {
					@Override
					public void onSendMessageSuccess(String arg0, Bundle arg1) {
						// TODO Auto-generated method stub
						
						//showToast("分享成功");
					}
					
					@Override
					public void onSendMessageFailed(String arg0, ShareMessageError e) {
						// TODO Auto-generated method stub

						showDialog("Error", e.getMessage());
					}
					
					@Override
					public void onSendMessageCanceled(String arg0) {
						// TODO Auto-generated method stub
						
					}
				});
    	
	}
	
	static void openUrl() {
		if (mActivity != null) {
			Intent intent = new Intent(Intent.ACTION_VIEW,
					Uri.parse("http://www.play.cn"));
			mActivity.startActivity(intent);
		}
	}

	static void shareToRenren(String filePath)
	{
		
		RennImgTextMessage message = new RennImgTextMessage();
		
		Bitmap bitmap = BitmapFactory.decodeFile(filePath);
		message.setThumbData(bitmap);
		message.setUrl("http://www.baidu.com");
		message.setTitle("别踩白猫儿！");
		message.setDescription("别踩白猫真是太好玩啦，我能玩出这样，你能么？");
		message.setMessageKey("renren");
		shareComponent.sendMessage(message, MessageTarget.TO_RENREN);
		bitmap.recycle();
	}
	
	static void shareToWeibo(String filePath)
	{
		Message msg = new Message();
		msg.what = Cocos2dxHandler.HANDLER_SEND_WEIBO;
		msg.obj = filePath;
		mHandler.sendMessage(msg);
	}

	void initWeixin()
	{
		api = WXAPIFactory.createWXAPI(this, WEIXIN_APP_ID);
		api.registerApp(WEIXIN_APP_ID);
	}
	
	static void shareToWeixin(String filePath)
	{
		if (api.isWXAppInstalled())
		{
			Bitmap bmp = BitmapFactory.decodeFile(filePath);
			WXImageObject imgObj = new WXImageObject(bmp);
			
			WXMediaMessage msg = new WXMediaMessage();
			msg.mediaObject = imgObj;
			
			Bitmap thumbBmp = Bitmap.createScaledBitmap(bmp, bmp.getWidth() / 10, bmp.getHeight() / 10, true);
			bmp.recycle();
			msg.thumbData = com.tencent.mm.sdk.platformtools.Util.bmpToByteArray(thumbBmp, true);  // 设置缩略图
	
			SendMessageToWX.Req req = new SendMessageToWX.Req();
			req.transaction = "img";
			req.message = msg;
			//req.scene = SendMessageToWX.Req.WXSceneTimeline;
			req.scene = SendMessageToWX.Req.WXSceneSession;
			api.sendReq(req);
		}
		
	}
	
	static void shareToPengyouquan(String filePath)
	{
		if (api.isWXAppInstalled())
		{
			Bitmap bmp = BitmapFactory.decodeFile(filePath);
			WXImageObject imgObj = new WXImageObject(bmp);

			WXMediaMessage msg = new WXMediaMessage();
			msg.mediaObject = imgObj;

			Bitmap thumbBmp = Bitmap.createScaledBitmap(bmp, bmp.getWidth() / 10, bmp.getHeight() / 10, true);
			bmp.recycle();
			msg.thumbData = com.tencent.mm.sdk.platformtools.Util.bmpToByteArray(thumbBmp, true);  // 设置缩略图

			SendMessageToWX.Req req = new SendMessageToWX.Req();
			req.transaction = "img";
			req.message = msg;
			req.scene = SendMessageToWX.Req.WXSceneTimeline;
			//req.scene = SendMessageToWX.Req.WXSceneSession;
			api.sendReq(req);

		}
	}
	
	// ===========================================================
	// Getter & Setter
	// ===========================================================

	// ===========================================================
	// Methods for/from SuperClass/Interfaces
	// ===========================================================

	@Override
	protected void onResume() {
		super.onResume();
		StatisticsEt.onResume();
		Cocos2dxHelper.onResume();
		this.mGLSurfaceView.onResume();
	}

	@Override
	protected void onPause() {
		super.onPause();
		StatisticsEt.onPause();
		Cocos2dxHelper.onPause();
		this.mGLSurfaceView.onPause();
	}

	@Override
	public void showDialog(final String pTitle, final String pMessage) {
		Message msg = new Message();
		msg.what = Cocos2dxHandler.HANDLER_SHOW_DIALOG;
		msg.obj = new Cocos2dxHandler.DialogMessage(pTitle, pMessage);
		this.mHandler.sendMessage(msg);
	}

	@Override
	public void showEditTextDialog(final String pTitle, final String pContent,
			final int pInputMode, final int pInputFlag, final int pReturnType,
			final int pMaxLength) {
		Message msg = new Message();
		msg.what = Cocos2dxHandler.HANDLER_SHOW_EDITBOX_DIALOG;
		msg.obj = new Cocos2dxHandler.EditBoxMessage(pTitle, pContent,
				pInputMode, pInputFlag, pReturnType, pMaxLength);
		this.mHandler.sendMessage(msg);
	}

	@Override
	public void runOnGLThread(final Runnable pRunnable) {
		this.mGLSurfaceView.queueEvent(pRunnable);
	}

	// ===========================================================
	// Methods
	// ===========================================================
	public void init() {

		// FrameLayout
		ViewGroup.LayoutParams framelayout_params = new ViewGroup.LayoutParams(
				ViewGroup.LayoutParams.MATCH_PARENT,
				ViewGroup.LayoutParams.MATCH_PARENT);
		FrameLayout framelayout = new FrameLayout(this);
		framelayout.setLayoutParams(framelayout_params);

		// Cocos2dxEditText layout
		ViewGroup.LayoutParams edittext_layout_params = new ViewGroup.LayoutParams(
				ViewGroup.LayoutParams.MATCH_PARENT,
				ViewGroup.LayoutParams.WRAP_CONTENT);
		Cocos2dxEditText edittext = new Cocos2dxEditText(this);
		edittext.setLayoutParams(edittext_layout_params);

		// ...add to FrameLayout
		framelayout.addView(edittext);

		// Cocos2dxGLSurfaceView
		this.mGLSurfaceView = this.onCreateView();

		// ...add to FrameLayout
		framelayout.addView(this.mGLSurfaceView);

		// Switch to supported OpenGL (ARGB888) mode on emulator
		if (isAndroidEmulator())
			this.mGLSurfaceView.setEGLConfigChooser(8, 8, 8, 8, 16, 0);

		this.mGLSurfaceView.setCocos2dxRenderer(new Cocos2dxRenderer());
		this.mGLSurfaceView.setCocos2dxEditText(edittext);

		// Set framelayout as the content view
		setContentView(framelayout);
	}

	public Cocos2dxGLSurfaceView onCreateView() {
		return new Cocos2dxGLSurfaceView(this);
	}

	private final static boolean isAndroidEmulator() {
		String model = Build.MODEL;
		Log.d(TAG, "model=" + model);
		String product = Build.PRODUCT;
		Log.d(TAG, "product=" + product);
		boolean isEmulator = false;
		if (product != null) {
			isEmulator = product.equals("sdk") || product.contains("_sdk")
					|| product.contains("sdk_");
		}
		Log.d(TAG, "isEmulator=" + isEmulator);
		return isEmulator;
	}

	// ===========================================================
	// Inner and Anonymous Classes
	// ===========================================================
}
