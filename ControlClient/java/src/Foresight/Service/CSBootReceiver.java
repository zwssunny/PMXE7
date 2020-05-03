package com.Foresight.Service;

import android.app.Activity;
import android.content.BroadcastReceiver;
import android.content.Intent;
import android.content.Context;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.net.NetworkInfo.State;

public class CSBootReceiver extends BroadcastReceiver
{

        @Override
        public void onReceive(Context context, Intent intent) 
        {
           ConnectivityManager mConnectivityManager = (ConnectivityManager) context.getSystemService(Context.CONNECTIVITY_SERVICE); 
	   NetworkInfo mNetworkInfo = mConnectivityManager.getActiveNetworkInfo(); 
	   if ((mNetworkInfo != null)&&(mNetworkInfo.isConnected())) { 
           	Intent launchintent = new Intent();
           	launchintent.setClassName(context, "com.embarcadero.firemonkey.FMXNativeActivity");           
           	launchintent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
           	context.startActivity(launchintent); 
         } 
        }

}