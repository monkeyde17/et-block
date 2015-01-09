/*
 * Copyright (C) 2010-2013 The SINA WEIBO Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package org.cocos2dx.weibo;

import android.text.TextUtils;

import com.sina.weibo.sdk.auth.Oauth2AccessToken;
import com.sina.weibo.sdk.net.AsyncWeiboRunner;
import com.sina.weibo.sdk.net.RequestListener;
import com.sina.weibo.sdk.net.WeiboParameters;
import com.sina.weibo.sdk.utils.LogUtil;

/**
 * ΢�� OpenAPI �Ļ��࣬ÿ���ӿ��඼�̳��˴˳����ࡣ
 * 
 * @author SINA
 * @since 2013-11-05
 */
public abstract class BAbsOpenAPI {
    private static final String TAG = BAbsOpenAPI.class.getName();
    
    /** ����΢������ӿڵĵ�ַ */
    protected static final String API_SERVER       = "https://api.weibo.com/2";
    /** POST ����ʽ */
    protected static final String HTTPMETHOD_POST  = "POST";
    /** GET ����ʽ */
    protected static final String HTTPMETHOD_GET   = "GET";
    /** HTTP ���� */
    protected static final String KEY_ACCESS_TOKEN = "access_token";
    
    /** ��ǰ�� Token */
    protected Oauth2AccessToken mAccessToken;

    /**
     * ���캯����ʹ�ø��� API �ӿ��ṩ�ķ���ǰ�����Ȼ�ȡ Token��
     * 
     * @param accesssToken ��������
     */
    public BAbsOpenAPI(Oauth2AccessToken accessToken) {
        mAccessToken = accessToken;
    }

    /**
     * HTTP �첽����
     * 
     * @param url        ����ĵ�ַ
     * @param params     ����Ĳ���
     * @param httpMethod ���󷽷�
     * @param listener   �����Ļص��ӿ�
     */
    protected void requestAsync(String url, WeiboParameters params, String httpMethod, RequestListener listener) {
        if (null == mAccessToken
                || TextUtils.isEmpty(url)
                || null == params
                || TextUtils.isEmpty(httpMethod)
                || null == listener) {
            LogUtil.e(TAG, "Argument error!");
            return;
        }
        
        params.put(KEY_ACCESS_TOKEN, mAccessToken.getToken());
        AsyncWeiboRunner.requestAsync(url, params, httpMethod, listener);
    }
    
    /**
     * HTTP ͬ������
     * 
     * @param url        ����ĵ�ַ
     * @param params     ����Ĳ���
     * @param httpMethod ���󷽷�
     * 
     * @return ͬ������󣬷��������ص��ַ�����
     */
    protected String requestSync(String url, WeiboParameters params, String httpMethod) {
        if (null == mAccessToken
                || TextUtils.isEmpty(url)
                || null == params
                || TextUtils.isEmpty(httpMethod)) {
            LogUtil.e(TAG, "Argument error!");
            return "";
        }
        
        params.put(KEY_ACCESS_TOKEN, mAccessToken.getToken());
        return AsyncWeiboRunner.request(url, params, httpMethod);
    }
}
