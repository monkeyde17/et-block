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

import android.graphics.Bitmap;
import android.text.TextUtils;
import android.util.SparseArray;

import com.sina.weibo.sdk.auth.Oauth2AccessToken;
import com.sina.weibo.sdk.net.RequestListener;
import com.sina.weibo.sdk.net.WeiboParameters;

/**
 * �����װ��΢���ӿڡ�
 * ������ο�<a href="http://t.cn/8F3e7SE">΢���ӿ�</a>
 * 
 * @author SINA
 * @since 2014-03-03
 */
public class BStatusesAPI extends BAbsOpenAPI {
    
    /** ��������ID��0��ȫ����1��ԭ����2��ͼƬ��3����Ƶ��4������ */
    public static final int FEATURE_ALL      = 0;
    public static final int FEATURE_ORIGINAL = 1;
    public static final int FEATURE_PICTURE  = 2;
    public static final int FEATURE_VIDEO    = 3;
    public static final int FEATURE_MUSICE   = 4;
    
    /** ����ɸѡ���ͣ�0��ȫ����1���ҹ�ע���ˡ�2��İ���� */
    public static final int AUTHOR_FILTER_ALL        = 0;
    public static final int AUTHOR_FILTER_ATTENTIONS = 1;
    public static final int AUTHOR_FILTER_STRANGER   = 2;
    
    /** ��Դɸѡ���ͣ�0��ȫ����1������΢�������ۡ�2������΢Ⱥ������ */
    public static final int SRC_FILTER_ALL      = 0;
    public static final int SRC_FILTER_WEIBO    = 1;
    public static final int SRC_FILTER_WEIQUN   = 2;
    
    /** ԭ��ɸѡ���ͣ�0��ȫ��΢����1��ԭ����΢����  */
    public static final int TYPE_FILTER_ALL     = 0;
    public static final int TYPE_FILTER_ORIGAL  = 1;    

    /** API URL */
    private static final String API_BASE_URL = API_SERVER + "/statuses";

    /**
     * API ���͡�
     * ��������
     *      <li>��ȡ�ӿڣ�READ_API_XXX
     *      <li>д��ӿڣ�WRITE_API_XXX
     * ��ע�⣺�����еĽӿڽ���Ϊ��ʾʹ�ã���û�а������й���΢���Ľӿڣ������������߿���
     * ������Ҫ�������࣬�ɲο�legacy���� {@link com.sina.weibo.sdk.openapi.legacy.StatusesAPI}
     */
    private static final int READ_API_FRIENDS_TIMELINE = 0;
    private static final int READ_API_MENTIONS         = 1;    
    private static final int WRITE_API_UPDATE          = 2;
    private static final int WRITE_API_REPOST          = 3;
    private static final int WRITE_API_UPLOAD          = 4;
    private static final int WRITE_API_UPLOAD_URL_TEXT = 5;

    private static final SparseArray<String> sAPIList = new SparseArray<String>();
    static {
        sAPIList.put(READ_API_FRIENDS_TIMELINE, API_BASE_URL + "/friends_timeline.json");
        sAPIList.put(READ_API_MENTIONS,         API_BASE_URL + "/mentions.json");
        sAPIList.put(WRITE_API_REPOST,          API_BASE_URL + "/repost.json");
        sAPIList.put(WRITE_API_UPDATE,          API_BASE_URL + "/update.json");
        sAPIList.put(WRITE_API_UPLOAD,          API_BASE_URL + "/upload.json");
        sAPIList.put(WRITE_API_UPLOAD_URL_TEXT, API_BASE_URL + "/upload_url_text.json");
    }

    /**
     * ���캯����ʹ�ø��� API �ӿ��ṩ�ķ���ǰ�����Ȼ�ȡ Token��
     * 
     * @param accesssToken ��������
     */
    public BStatusesAPI(Oauth2AccessToken accessToken) {
        super(accessToken);
    }
    
    /**
     * ��ȡ��ǰ��¼�û���������ע�û�������΢����
     * 
     * @param since_id    ��ָ���˲������򷵻�ID��since_id���΢��������since_idʱ�����΢������Ĭ��Ϊ0
     * @param max_id      ��ָ���˲������򷵻�IDС�ڻ����max_id��΢����Ĭ��Ϊ0��
     * @param count       ��ҳ���صļ�¼������Ĭ��Ϊ50��
     * @param page        ���ؽ����ҳ�룬Ĭ��Ϊ1��
     * @param base_app    �Ƿ�ֻ��ȡ��ǰӦ�õ����ݡ�falseΪ���������ݣ���trueΪ�ǣ�����ǰӦ�ã���Ĭ��Ϊfalse��
     * @param featureType ��������ID��0��ȫ����1��ԭ����2��ͼƬ��3����Ƶ��4�����֣�Ĭ��Ϊ0��
     *                    <li>{@link #FEATURE_ALL}
     *                    <li>{@link #FEATURE_ORIGINAL}
     *                    <li>{@link #FEATURE_PICTURE}
     *                    <li>{@link #FEATURE_VIDEO}
     *                    <li>{@link #FEATURE_MUSICE}
     * @param trim_user   ����ֵ��user�ֶο��أ�false����������user�ֶΡ�true��user�ֶν�����user_id��Ĭ��Ϊfalse��
     * @param listener    �첽����ص��ӿ�
     */
    public void friendsTimeline(long since_id, long max_id, int count, int page, boolean base_app,
            int featureType, boolean trim_user, RequestListener listener) {
        WeiboParameters params = 
                buildTimeLineParamsBase(since_id, max_id, count, page, base_app, trim_user, featureType);
        requestAsync(sAPIList.get(READ_API_FRIENDS_TIMELINE), params, HTTPMETHOD_GET, listener);
    }    
    
    /**
     * ��ȡ���µ��ᵽ��¼�û���΢���б���@�ҵ�΢����
     * 
     * @param since_id      ��ָ���˲������򷵻�ID��since_id���΢��������since_idʱ�����΢������Ĭ��Ϊ0��
     * @param max_id        ��ָ���˲������򷵻�IDС�ڻ����max_id��΢����Ĭ��Ϊ0��
     * @param count         ��ҳ���صļ�¼������Ĭ��Ϊ50��
     * @param page          ���ؽ����ҳ�룬Ĭ��Ϊ1��
     * @param authorType    ����ɸѡ���ͣ�0��ȫ����1���ҹ�ע���ˡ�2��İ���� ,Ĭ��Ϊ0����Ϊ���¼��� :
     *                      <li>{@link #AUTHOR_FILTER_ALL}
     *                      <li>{@link #AUTHOR_FILTER_ATTENTIONS}
     *                      <li>{@link #AUTHOR_FILTER_STRANGER}
     * @param sourceType    ��Դɸѡ���ͣ�0��ȫ����1������΢�������ۡ�2������΢Ⱥ�����ۣ�Ĭ��Ϊ0����Ϊ���¼��� :
     *                      <li>{@link #SRC_FILTER_ALL}
     *                      <li>{@link #SRC_FILTER_WEIBO}
     *                      <li>{@link #SRC_FILTER_WEIQUN}
     * @param filterType    ԭ��ɸѡ���ͣ�0��ȫ��΢����1��ԭ����΢����Ĭ��Ϊ0�� ��Ϊ���¼��� :
     *                      <li>{@link #TYPE_FILTER_ALL}
     *                      <li>{@link #TYPE_FILTER_ORIGAL}
     * @param trim_user     ����ֵ��user�ֶο��أ�false����������user�ֶΡ�true��user�ֶν�����user_id��Ĭ��Ϊfalse
     * @param listener      �첽����ص��ӿ�
     */
    public void mentions(long since_id, long max_id, int count, int page, int authorType, int sourceType,
            int filterType, boolean trim_user, RequestListener listener) {
        WeiboParameters params = buildMentionsParams(since_id, max_id, count, page, authorType, sourceType, filterType, trim_user);
        requestAsync(sAPIList.get(READ_API_MENTIONS), params, HTTPMETHOD_GET, listener);
    }
    
    /**
     * ����һ����΢�����������η�����΢���������ظ�����
     * 
     * @param content  Ҫ������΢���ı����ݣ����ݲ�����140�����֡�
     * @param lat      γ�ȣ���Ч��Χ��-90.0��+90.0��+��ʾ��γ��Ĭ��Ϊ0.0��
     * @param lon      ���ȣ���Ч��Χ��-180.0��+180.0��+��ʾ������Ĭ��Ϊ0.0��
     * @param listener �첽����ص��ӿ�
     */
    public void update(String content, String lat, String lon, RequestListener listener) {
        WeiboParameters params = buildUpdateParams(content, lat, lon);
        requestAsync(sAPIList.get(WRITE_API_UPDATE), params, HTTPMETHOD_POST, listener);
    }
    
    /**
     * �ϴ�ͼƬ������һ����΢����
     * 
     * @param content  Ҫ������΢���ı����ݣ����ݲ�����140������
     * @param bitmap   Ҫ�ϴ���ͼƬ����֧��JPEG��GIF��PNG��ʽ��ͼƬ��СС��5M
     * @param lat      γ�ȣ���Ч��Χ��-90.0��+90.0��+��ʾ��γ��Ĭ��Ϊ0.0��
     * @param lon      ���ȣ���Ч��Χ��-180.0��+180.0��+��ʾ������Ĭ��Ϊ0.0��
     * @param listener �첽����ص��ӿ�
     */
    public void upload(String content, Bitmap bitmap, String lat, String lon, RequestListener listener) {
        WeiboParameters params = buildUpdateParams(content, lat, lon);
        params.put("pic", bitmap);
        requestAsync(sAPIList.get(WRITE_API_UPLOAD), params, HTTPMETHOD_POST, listener);
    }
    
    /**
     * ָ��һ��ͼƬURL��ַץȡ���ϴ���ͬʱ����һ����΢�����˷����ᴦ��URLencod��
     * 
     * @param status   Ҫ������΢���ı����ݣ����ݲ�����140�����֡�
     * @param imageUrl ͼƬ��URL��ַ��������http��ͷ��
     * @param pic_id   �Ѿ��ϴ���ͼƬpid�����ʱʹ��Ӣ�İ�Ƕ��ŷ��ָ�����಻�������š� 
     *                 imageUrl �� pic_id��ѡһ������������������ʱ��ȡpicid������ֵΪ׼��
     *                 <b>ע��Ŀǰ�ò��������ã����ڻ�ֻ��ͨ��BD�������룬���Ը�������</b>
     * @param lat      γ�ȣ���Ч��Χ��-90.0��+90.0��+��ʾ��γ��Ĭ��Ϊ0.0��
     * @param lon      ���ȣ���Ч��Χ��-180.0��+180.0��+��ʾ������Ĭ��Ϊ0.0��
     * @param listener �첽����ص��ӿ�
     */
    public void uploadUrlText(String status, String imageUrl, String pic_id, String lat, String lon,
            RequestListener listener) {
        WeiboParameters params = buildUpdateParams(status, lat, lon);
        params.put("url", imageUrl);
        params.put("pic_id", pic_id);
        requestAsync(sAPIList.get(WRITE_API_UPLOAD_URL_TEXT), params, HTTPMETHOD_POST, listener);
    }
    
    /**
     * @see #friendsTimeline(long, long, int, int, boolean, int, boolean, RequestListener)
     */
    public String friendsTimelineSync(long since_id, long max_id, int count, int page, boolean base_app, int featureType,
            boolean trim_user) {
        WeiboParameters params = buildTimeLineParamsBase(since_id, max_id, count, page, base_app,
                trim_user, featureType);
        return requestSync(sAPIList.get(READ_API_FRIENDS_TIMELINE), params, HTTPMETHOD_GET);
    }

    /**
     * -----------------------------------------------------------------------
     * ��ע�⣺���·����Ⱦ�ͬ��������������������Լ����첽������ƣ���ʹ�øú�����
     * -----------------------------------------------------------------------
     */
    
    /**
     * @see #mentions(long, long, int, int, int, int, int, boolean, RequestListener)
     */
    public String mentionsSync(long since_id, long max_id, int count, int page,
            int authorType, int sourceType, int filterType, boolean trim_user) {
        WeiboParameters params = buildMentionsParams(since_id, max_id, count, page, authorType, sourceType, filterType, trim_user);
        return requestSync(sAPIList.get(READ_API_MENTIONS), params, HTTPMETHOD_GET);
    }

    /**
     * @see #update(String, String, String, RequestListener)
     */
    public String updateSync(String content, String lat, String lon) {
        WeiboParameters params = buildUpdateParams(content, lat, lon);
        return requestSync(sAPIList.get(WRITE_API_UPDATE), params, HTTPMETHOD_POST);
    }

    /**
     * @see #upload(String, Bitmap, String, String, RequestListener)
     */
    public String uploadSync(String content, Bitmap bitmap, String lat, String lon) {
        WeiboParameters params = buildUpdateParams(content, lat, lon);
        params.put("pic", bitmap);
        return requestSync(sAPIList.get(WRITE_API_UPLOAD), params, HTTPMETHOD_POST);
    }

    /**
     * @see #uploadUrlText(String, String, String, String, String, RequestListener)
     */
    public String uploadUrlTextSync(String status, String imageUrl, String pic_id, String lat, String lon) {
        WeiboParameters params = buildUpdateParams(status, lat, lon);
        params.put("url", imageUrl);
        params.put("pic_id", pic_id);
        return requestSync(sAPIList.get(WRITE_API_UPLOAD_URL_TEXT), params, HTTPMETHOD_POST);
    }

    // ��װTimeLines�Ĳ���
    private WeiboParameters buildTimeLineParamsBase(long since_id, long max_id, int count, int page,
            boolean base_app, boolean trim_user, int featureType) {
        WeiboParameters params = new WeiboParameters();
        params.put("since_id", since_id);
        params.put("max_id", max_id);
        params.put("count", count);
        params.put("page", page);
        params.put("base_app", base_app ? 1 : 0);
        params.put("trim_user", trim_user ? 1 : 0);
        params.put("feature", featureType);
        return params;
    }

    // ��װ΢���������
    private WeiboParameters buildUpdateParams(String content, String lat, String lon) {
        WeiboParameters params = new WeiboParameters();
        params.put("status", content);
        if (!TextUtils.isEmpty(lon)) {
            params.put("long", lon);
        }
        if (!TextUtils.isEmpty(lat)) {
            params.put("lat", lat);
        }
        return params;
    }
    
    private WeiboParameters buildMentionsParams(long since_id, long max_id, int count, int page,
            int authorType, int sourceType, int filterType, boolean trim_user) {
        WeiboParameters params = new WeiboParameters();
        params.put("since_id", since_id);
        params.put("max_id", max_id);
        params.put("count", count);
        params.put("page", page);
        params.put("filter_by_author", authorType);
        params.put("filter_by_source", sourceType);
        params.put("filter_by_type", filterType);
        params.put("trim_user", trim_user ? 1 : 0);
        
        return params;
    } 
}
