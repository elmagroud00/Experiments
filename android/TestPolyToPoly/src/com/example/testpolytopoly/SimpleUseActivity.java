package com.example.testpolytopoly;

import android.app.Activity;
import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.LinearGradient;
import android.graphics.Matrix;
import android.graphics.Paint;
import android.graphics.Paint.Style;
import android.graphics.Shader.TileMode;
import android.os.Bundle;
import android.view.View;

public class SimpleUseActivity extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(new PolyToPolyView(this));
	}

	class PolyToPolyView extends View {
		private static final int NUM_OF_POINT = 8;

		private int mTranslateDis;
		private float mFactor = 0.8f;
		private int mNumOfFolds = 8;
		private Matrix[] mMatrics = new Matrix[mNumOfFolds];
		private Bitmap mBitmap;
		private Paint mSolidPaint;
		private Paint mShadowPaint;
		private Matrix mShadowGradientMatrix;
		private LinearGradient mShadowGradientShader;
		private int mFlodWidth;
		private int mTranslateDisPerFlod;

		public PolyToPolyView(Context context) {
			super(context);
			mBitmap = BitmapFactory.decodeResource(getResources(),
					R.drawable.jobs);
			mTranslateDis = (int) (mBitmap.getWidth() * mFactor);
			mFlodWidth = mBitmap.getWidth() / mNumOfFolds;

			for (int i = 0; i < mNumOfFolds; i++) {
				mMatrics[i] = new Matrix();
			}

			mSolidPaint = new Paint();
			int alpha = (int) (255 * mFactor * 0.8f);
			mSolidPaint.setColor(Color.argb((int) (alpha * 0.8f), 0, 0, 0));
			mShadowPaint = new Paint();
			mShadowPaint.setStyle(Style.FILL);
			mShadowGradientShader = new LinearGradient(0, 0, 0.5f, 0,
					Color.BLACK, Color.TRANSPARENT, TileMode.CLAMP);
			mShadowPaint.setShader(mShadowGradientShader);
			mShadowGradientMatrix = new Matrix();
			mShadowGradientMatrix.setScale(mFlodWidth, 1);
			mShadowGradientShader.setLocalMatrix(mShadowGradientMatrix);
			mShadowPaint.setAlpha(alpha);

			int depth = (int) Math.sqrt(mFlodWidth * mFlodWidth
					- mTranslateDisPerFlod * mTranslateDisPerFlod) / 2;
			float[] src = new float[NUM_OF_POINT];
			float[] dst = new float[NUM_OF_POINT];

			for (int i = 0; i < mNumOfFolds; i++) {
				src[0] = i * mFlodWidth;
				src[1] = 0;
				src[2] = src[0] + mFlodWidth;
				src[3] = 0;
				src[4] = src[2];
				src[5] = mBitmap.getHeight();
				src[6] = src[0];
				src[7] = src[5];

				boolean isEven = i % 2 == 0;

				dst[0] = i * mTranslateDisPerFlod;
				dst[1] = isEven ? 0 : depth;
				dst[2] = dst[0] + mTranslateDisPerFlod;
				dst[3] = isEven ? depth : 0;
				dst[4] = dst[2];
				dst[5] = isEven ? mBitmap.getHeight() - depth : mBitmap
						.getHeight();
				dst[6] = dst[0];
				dst[7] = isEven ? mBitmap.getHeight() : mBitmap.getHeight()
						- depth;

				mMatrics[i].setPolyToPoly(src, 0, dst, 0, src.length >> 1);

			}

		}

		@Override
		protected void onDraw(Canvas canvas) {
			super.onDraw(canvas);
			for (int i = 0; i < mNumOfFolds; i++) {
				canvas.save();
				canvas.concat(mMatrics[i]);
				canvas.clipRect(mFlodWidth * i, 0, mFlodWidth * i + mFlodWidth,
						mBitmap.getHeight());
				canvas.drawBitmap(mBitmap, 0, 0, null);
				canvas.translate(mFlodWidth * i, 0);
				if (i % 2 == 0) {
					canvas.drawRect(0, 0, mFlodWidth, mBitmap.getHeight(),
							mSolidPaint);
				} else {
					canvas.drawRect(0, 0, mFlodWidth, mBitmap.getHeight(),
							mShadowPaint);
				}
				canvas.restore();
			}
		}
	}
}
