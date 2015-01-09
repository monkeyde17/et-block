/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org

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

import java.lang.ref.WeakReference;

import org.cocos2dx.weibo.BStatusesAPI;




import com.sina.weibo.sdk.auth.Oauth2AccessToken;
import com.sina.weibo.sdk.auth.WeiboAuth;
import com.sina.weibo.sdk.auth.WeiboAuthListener;
import com.sina.weibo.sdk.constant.WBConstants;
import com.sina.weibo.sdk.exception.WeiboException;
import com.sina.weibo.sdk.net.AsyncWeiboRunner;
import com.sina.weibo.sdk.net.RequestListener;
import com.sina.weibo.sdk.net.WeiboParameters;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.widget.Toast;

public class Cocos2dxHandler extends Handler {
	
	// weibo
		private static String mCode;
		
		private static String weiboFilePath;
		
		private static WeiboAuth weiboAuth;
		
	    private static final String OAUTH2_ACCESS_TOKEN_URL = "https://open.weibo.cn/oauth2/access_token";
	    
		private static final String WEIBO_APP_ID = "1118822269";
		
		private static final String WEIBO_APP_SECRET = "d53c531929fc9c729dcc90f71b2a2427";
		
		private static final String WEIBO_URL = "http://www.baidu.com";
		
		private static final String WEIBO_SCOPE = "email,direct_messages_read,direct_messages_write,"
	+ "friendships_groups_read,friendships_groups_write,statuses_to_me_read,"
	+ "follow_app_official_microblog," + "invitation_write";
		
	// ===========================================================
	// Constants
	// ===========================================================
	public final static int HANDLER_SHOW_DIALOG = 1;
	public final static int HANDLER_SHOW_EDITBOX_DIALOG = 2;
	public final static int HANDLER_SEND_WEIBO = 3;
	public final static int HANDLER_BACK_KEY = 4;
	public final static int HANDLER_SHOW_TOAST = 5;
	// ===========================================================
	// Fields
	// ===========================================================
	private WeakReference<Cocos2dxActivity> mActivity;
	
	// ===========================================================
	// Constructors
	// ===========================================================
	public Cocos2dxHandler(Cocos2dxActivity activity) {
		this.mActivity = new WeakReference<Cocos2dxActivity>(activity);
	}

	// ===========================================================
	// Getter & Setter
	// ===========================================================

	// ===========================================================
	// Methods for/from SuperClass/Interfaces
	// ===========================================================
	
	// ===========================================================
	// Methods
	// ===========================================================

	public void handleMessage(Message msg) {
		switch (msg.what) {
		case Cocos2dxHandler.HANDLER_SHOW_DIALOG:
			showDialog(msg);
			break;
		case Cocos2dxHandler.HANDLER_SHOW_EDITBOX_DIALOG:
			showEditBoxDialog(msg);
			break;
		case Cocos2dxHandler.HANDLER_SEND_WEIBO:
			sendToWeibo(msg);
			break;
		case Cocos2dxHandler.HANDLER_BACK_KEY:
			showExit();
			break;
		case Cocos2dxHandler.HANDLER_SHOW_TOAST:
			showToast(msg);
			break;
		}
	}
	public class AuthListener implements WeiboAuthListener{

		@Override
		public void onCancel() {
		}

		@Override
		public void onComplete(Bundle arg0) {
			// TODO Auto-generated method stub
			String code = arg0.getString("code");
            mCode = code;
            fetchTokenAsync(mCode, WEIBO_APP_SECRET);
		}

		@Override
		public void onWeiboException(WeiboException arg0) {
			showToast("Share Fail!");
		}
	}
	
	public class WeiBoRequestListener implements RequestListener {

		@Override
		public void onComplete(String arg0) {
			showToast("Share Success!");
		}

		@Override
		public void onWeiboException(WeiboException arg0) {
			showToast("Share Fail!");
		}
	
	}
	
	public void fetchTokenAsync(String authCode, String appSecret) {
        
        WeiboParameters requestParams = new WeiboParameters();
        requestParams.put(WBConstants.AUTH_PARAMS_CLIENT_ID,     WEIBO_APP_ID);
        requestParams.put(WBConstants.AUTH_PARAMS_CLIENT_SECRET, appSecret);
        requestParams.put(WBConstants.AUTH_PARAMS_GRANT_TYPE,    "authorization_code");
        requestParams.put(WBConstants.AUTH_PARAMS_CODE,          authCode);
        requestParams.put(WBConstants.AUTH_PARAMS_REDIRECT_URL,  WEIBO_URL);
        
        // 异步请求，获取 Token
        AsyncWeiboRunner.requestAsync(OAUTH2_ACCESS_TOKEN_URL, requestParams, "POST", new RequestListener() {
            @Override
            public void onComplete(String response) {
                
                // 获取 Token 成功
                Oauth2AccessToken token = Oauth2AccessToken.parseAccessToken(response);
                if (token != null && token.isSessionValid()) {
                    BStatusesAPI statusesAPI = new BStatusesAPI(token);
                    Bitmap bitmap = BitmapFactory.decodeFile(weiboFilePath);
                    statusesAPI.upload("The Running Ball is pretty cool!!!", bitmap, null, null, new WeiBoRequestListener()); 
                } else {
                	
                }
            }

            @Override
            public void onWeiboException(WeiboException e) {
            	showToast("Share Fail!");
			}
        });
    }
	
	private void sendToWeibo(Message msg)
	{
		weiboAuth = new WeiboAuth(this.mActivity.get(), WEIBO_APP_ID, WEIBO_URL, WEIBO_SCOPE);
		weiboFilePath = (String)msg.obj;
		weiboAuth.authorize(new AuthListener(), WeiboAuth.OBTAIN_AUTH_CODE);
	}
	
	private void showToast(String msg)
	{
		Toast.makeText(this.mActivity.get(), msg.toString(), Toast.LENGTH_SHORT).show();
	}
	
	private void showToast(Message msg)
	{
		Toast.makeText(this.mActivity.get(), msg.obj.toString(), Toast.LENGTH_SHORT).show();
	}
	
	private void showExit() {
		Cocos2dxActivity theActivity = this.mActivity.get();
		new AlertDialog.Builder(theActivity)
		//.setTitle(dialogMessage.titile)
		.setMessage("是否退出？")
		.setPositiveButton("确定", 
				new DialogInterface.OnClickListener() {
					
					@Override
					public void onClick(DialogInterface dialog, int which) {
						// TODO Auto-generated method stub
						//mActivity.finish();
						System.exit(0);
					}
				})
		.setNegativeButton("取消", new DialogInterface.OnClickListener() {
			
			@Override
			public void onClick(DialogInterface dialog, int which) {
				// TODO Auto-generated method stub
			}
		}).create().show();
	}
	
	
	private void showDialog(Message msg) {
		Cocos2dxActivity theActivity = this.mActivity.get();
		DialogMessage dialogMessage = (DialogMessage)msg.obj;
		new AlertDialog.Builder(theActivity)
		.setTitle(dialogMessage.titile)
		.setMessage(dialogMessage.message)
		.setPositiveButton("Ok", 
				new DialogInterface.OnClickListener() {
					
					@Override
					public void onClick(DialogInterface dialog, int which) {
						// TODO Auto-generated method stub
						
					}
				}).create().show();
	}
	
	private void showEditBoxDialog(Message msg) {
		EditBoxMessage editBoxMessage = (EditBoxMessage)msg.obj;
		new Cocos2dxEditBoxDialog(this.mActivity.get(),
				editBoxMessage.title,
				editBoxMessage.content,
				editBoxMessage.inputMode,
				editBoxMessage.inputFlag,
				editBoxMessage.returnType,
				editBoxMessage.maxLength).show();
	}
	
	
	// ===========================================================
	// Inner and Anonymous Classes
	// ===========================================================
	
	public static class DialogMessage {
		public String titile;
		public String message;
		
		public DialogMessage(String title, String message) {
			this.titile = title;
			this.message = message;
		}
	}
	
	public static class EditBoxMessage {
		public String title;
		public String content;
		public int inputMode;
		public int inputFlag;
		public int returnType;
		public int maxLength;
		
		public EditBoxMessage(String title, String content, int inputMode, int inputFlag, int returnType, int maxLength){
			this.content = content;
			this.title = title;
			this.inputMode = inputMode;
			this.inputFlag = inputFlag;
			this.returnType = returnType;
			this.maxLength = maxLength;
		}
	}
}
