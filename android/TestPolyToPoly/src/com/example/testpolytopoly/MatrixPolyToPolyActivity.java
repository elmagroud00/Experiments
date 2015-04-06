package com.example.testpolytopoly;

import android.app.Activity;
import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Matrix;
import android.os.Bundle;
import android.view.View;

public class MatrixPolyToPolyActivity extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(new PolyToPolyView(this));
	}

	class PolyToPolyView extends View {
		private Bitmap mBitmap;
		private Matrix mMatrix;

		public PolyToPolyView(Context context) {
			super(context);
			mBitmap = BitmapFactory.decodeResource(getResources(),
					R.drawable.jobs);
			mMatrix = new Matrix();
			float[] src = { 0, 0, mBitmap.getWidth(), 0, mBitmap.getWidth(),
					mBitmap.getHeight(), 0, mBitmap.getHeight() };
			float[] dst = { 0, 0, mBitmap.getWidth(), 400, mBitmap.getWidth(),
					mBitmap.getHeight() - 400, 0, mBitmap.getHeight() };
			mMatrix.setPolyToPoly(src, 0, dst, 0, src.length >> 1);
		}

		@Override
		protected void onDraw(Canvas canvas) {
			super.onDraw(canvas);
			canvas.drawBitmap(mBitmap, mMatrix, null);
		}

	}
}
