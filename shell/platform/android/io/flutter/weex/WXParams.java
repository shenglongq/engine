package com.beanfactory.doumi;

import java.util.Map;

public class WXParams {

    private String platform;
    private String osVersion;
    private String appVersion;
    private String weexVersion;
    private String deviceModel;
    private String appName;
    private String deviceWidth;
    private String deviceHeight;
    private String shouldInfoCollect;
    private String logLevel;
    private String needInitV8;
    private Map<String, String> options;

    public WXParams() {
    }

    public Object getOptions() {
        return this.options;
    }

    public void setOptions(Map<String, String> options) {
        this.options = options;
    }

    public String getShouldInfoCollect() {
        return this.shouldInfoCollect;
    }

    public void setShouldInfoCollect(String shouldInfoCollect) {
        this.shouldInfoCollect = shouldInfoCollect;
    }

    public String getPlatform() {
        return this.platform;
    }

    public void setPlatform(String platform) {
        this.platform = platform;
    }

    public String getOsVersion() {
        return this.osVersion;
    }

    public void setOsVersion(String osVersion) {
        this.osVersion = osVersion;
    }

    public String getAppVersion() {
        return this.appVersion;
    }

    public void setAppVersion(String appVersion) {
        this.appVersion = appVersion;
    }

    public String getWeexVersion() {
        return this.weexVersion;
    }

    public void setWeexVersion(String weexVersion) {
        this.weexVersion = weexVersion;
    }

    public String getDeviceModel() {
        return this.deviceModel;
    }

    public void setDeviceModel(String deviceModel) {
        this.deviceModel = deviceModel;
    }

    public String getAppName() {
        return this.appName;
    }

    public void setAppName(String appName) {
        this.appName = appName;
    }

    public String getDeviceWidth() {
        return this.deviceWidth;
    }

    /** @deprecated */
    @Deprecated
    public void setDeviceWidth(String deviceWidth) {
        this.deviceWidth = deviceWidth;
    }

    public String getDeviceHeight() {
        return this.deviceHeight;
    }

    public void setDeviceHeight(String deviceHeight) {
        this.deviceHeight = deviceHeight;
    }

    public String getLogLevel() {
        return this.logLevel == null?"":this.logLevel;
    }

    public void setLogLevel(String logLevel) {
        this.logLevel = logLevel;
    }

    public String getNeedInitV8() {
        return this.needInitV8 == null?"":this.needInitV8;
    }

    public void setNeedInitV8(boolean need) {
        if(need) {
            this.needInitV8 = "1";
        } else {
            this.needInitV8 = "0";
        }

    }
}