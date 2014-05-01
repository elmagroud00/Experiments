package com.example.openglexample;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;
import android.opengl.GLSurfaceView;

public class PyramidRenderer implements GLSurfaceView.Renderer {
	private boolean mTranslucentBackground;
	private Pyramid mPyramid;
	private float mAngle, mAngleDelta = 0;
	private float mCenter[] = {0, 0, -10};
	private float mVel[] = {0.025f, 0.03535227f, 0f};
	
	public PyramidRenderer(boolean useTranslucentBackground) {
		mTranslucentBackground = useTranslucentBackground;
		mPyramid = new Pyramid();
	}
	
	@Override
	public void onDrawFrame(GL10 gl) {
		gl.glClear(GL10.GL_COLOR_BUFFER_BIT | GL10.GL_DEPTH_BUFFER_BIT);
		
		gl.glMatrixMode(GL10.GL_MODELVIEW);
		gl.glLoadIdentity();
		gl.glTranslatef(mCenter[0], mCenter[1], mCenter[2]);
		gl.glRotatef(mAngle, 0, 1, 0);
		gl.glRotatef(mAngle * 0.25f, 1, 0, 0);
		
		gl.glEnableClientState(GL10.GL_VERTEX_ARRAY);
		gl.glEnableClientState(GL10.GL_COLOR_ARRAY);
		mPyramid.draw(gl);
		
		mAngle += mAngleDelta;
		
		mCenter[0] += mVel[0];
		mCenter[1] += mVel[1];
		
		if(Math.abs(mCenter[0]) > 4.0f) {
			mVel[0] = -mVel[0];
			mAngleDelta = (float)(5 * (0.5 - Math.random()));
		}
		if(Math.abs(mCenter[1]) > 6.0f) {
			mVel[1] = -mVel[1];
			mAngleDelta = (float)(5 * (0.5 - Math.random()));
		}
	}
	
	@Override
	public void onSurfaceChanged(GL10 gl, int width, int height) {
		gl.glViewport(0, 0, width, height);
		float ratio = (float)width / height;
		gl.glMatrixMode(GL10.GL_PROJECTION);
		gl.glLoadIdentity();
		gl.glFrustumf(-ratio, ratio, -1, 1, 1, 20);
	}

	@Override
	public void onSurfaceCreated(GL10 gl, EGLConfig config) {
		gl.glDisable(GL10.GL_DITHER);
		gl.glHint(GL10.GL_PERSPECTIVE_CORRECTION_HINT, GL10.GL_FASTEST);
		
		if(mTranslucentBackground) {
			gl.glClearColor(0, 0, 0, 0);
		} else {
			gl.glClearColor(1, 1, 1, 1);
		}
		gl.glEnable(GL10.GL_CULL_FACE);
		gl.glShadeModel(GL10.GL_SMOOTH);
		gl.glEnable(GL10.GL_DEPTH_TEST);		
	}
}












