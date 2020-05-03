package com.foresight.Zxing.barcode;
import android.content.Intent;
import android.os.Bundle;

import com.embarcadero.firemonkey.FMXNativeActivity;

public class NativeActivityExt extends FMXNativeActivity {
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
	}

	/* 调用delphi本地方法*/
	public native boolean onActivityResultNative(int requestCode, int resultCode, Intent data);
	
	@Override
	protected void onActivityResult(int requestCode, int resultCode, Intent data){
		if (!onActivityResultNative(requestCode, resultCode, data))
			super.onActivityResult(requestCode, resultCode, data);
	}
}
