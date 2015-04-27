package com.example.testblance;

import android.app.Activity;
import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.BitmapFactory.Options;
import android.graphics.Canvas;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.os.PowerManager;
import android.os.PowerManager.WakeLock;
import android.util.DisplayMetrics;
import android.view.Display;
import android.view.Surface;
import android.view.View;
import android.view.WindowManager;

public class MainActivity extends Activity {
    private SimulationView mSimulationView; // 游戏主显示View
    private SensorManager mSensorManager; // 感应器管理类
    private PowerManager mPowerManager; // 电源控制，比如防锁屏
    private WindowManager mWindowManager;
    private Display mDisplay;
    private WakeLock mWakeLock;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        mSensorManager = (SensorManager) getSystemService(SENSOR_SERVICE); // 实例化感应器管理类
        mPowerManager = (PowerManager) getSystemService(POWER_SERVICE);
        mWindowManager = (WindowManager) getSystemService(WINDOW_SERVICE);
        mDisplay = mWindowManager.getDefaultDisplay(); // 为了获取屏幕的DPI级别
        mWakeLock = mPowerManager.newWakeLock(
                PowerManager.SCREEN_BRIGHT_WAKE_LOCK, getClass().getName()); // 处理屏幕防止锁屏
        mSimulationView = new SimulationView(this);
        setContentView(mSimulationView); // 设置游戏View
    }

    @Override
    protected void onResume() {
        super.onResume();
        mWakeLock.acquire(); // 恢复时解除锁屏
        mSimulationView.startSimulation();
    }

    @Override
    protected void onPause() {
        super.onPause();
        mSimulationView.stopSimulation(); // Activity切出去时停止画面更新
        mWakeLock.release();
    }

    class SimulationView extends View implements SensorEventListener {
        private static final float sBallDiameter = 0.004f; // 设置小球直径
        private static final float sBallDiameter2 = sBallDiameter
                * sBallDiameter;
        private static final float sFriction = 0.1f; // 摩擦系数
        private Sensor mAccelerometer;
        private long mLastT;
        private float mLastDeltaT;
        private float mXDpi;
        private float mYDpi;
        private float mMetersToPixelsX;
        private float mMetersToPixelsY;
        private Bitmap mBitmap; // 小球素材
        private Bitmap mWood; // 背景使用木头
        private float mXOrigin;
        private float mYOrigin;
        private float mSensorX;
        private float mSensorY;
        private long mSensorTimeStamp;
        private long mCpuTimeStamp;
        private float mHorizontalBound;
        private float mVerticalBound;
        private final ParticleSystem mParticleSystem = new ParticleSystem();

        class Particle {
            private float mPosX;
            private float mPosY;
            private float mAccelX;
            private float mAccelY;
            private float mLastPosX;
            private float mLastPosY;
            private float mOneMinusFriction;

            Particle() {
                final float r = ((float) Math.random() - 0.5f) * 0.2f;
                mOneMinusFriction = 1.0f - sFriction + r;
            }

            public void computePhysics(float sx, float sy, float dT, float dTC) {
                final float m = 1000.0f; // mass of our virtual object
                final float gx = -sx * m;
                final float gy = -sy * m;
                final float invm = 1.0f / m;
                final float ax = gx * invm;
                final float ay = gy * invm;
                final float dTdT = dT * dT;
                final float x = mPosX + mOneMinusFriction * dTC
                        * (mPosX - mLastPosX) + mAccelX * dTdT;
                final float y = mPosY + mOneMinusFriction * dTC
                        * (mPosY - mLastPosY) + mAccelY * dTdT;
                mLastPosX = mPosX;
                mLastPosY = mPosY;
                mPosX = x;
                mPosY = y;
                mAccelX = ax;
                mAccelY = ay;
            }

            public void resolveCollisionWithBounds() {
                final float xmax = mHorizontalBound;
                final float ymax = mVerticalBound;
                final float x = mPosX;
                final float y = mPosY;
                if (x > xmax) {
                    mPosX = xmax;
                } else if (x < -xmax) {
                    mPosX = -xmax;
                }
                if (y > ymax) {
                    mPosY = ymax;
                } else if (y < -ymax) {
                    mPosY = -ymax;
                }
            }
        }

        class ParticleSystem { // 收集取样感应器数据来绘制小球位置
            static final int NUM_PARTICLES = 15;
            private Particle mBalls[] = new Particle[NUM_PARTICLES];

            ParticleSystem() {
                for (int i = 0; i < mBalls.length; i++) {
                    mBalls[i] = new Particle();
                }
            }

            private void updatePositions(float sx, float sy, long timestamp) {
                final long t = timestamp;
                if (mLastT != 0) {
                    final float dT = (float) (t - mLastT)
                            * (1.0f / 1000000000.0f);
                    if (mLastDeltaT != 0) {
                        final float dTC = dT / mLastDeltaT;
                        final int count = mBalls.length;
                        for (int i = 0; i < count; i++) {
                            Particle ball = mBalls[i];
                            ball.computePhysics(sx, sy, dT, dTC);
                        }
                    }
                    mLastDeltaT = dT;
                }
                mLastT = t;
            }

            public void update(float sx, float sy, long now) {
                updatePositions(sx, sy, now);
                final int NUM_MAX_ITERATIONS = 10;
                boolean more = true;
                final int count = mBalls.length;
                for (int k = 0; k < NUM_MAX_ITERATIONS && more; k++) {
                    more = false;
                    for (int i = 0; i < count; i++) {
                        Particle curr = mBalls[i];
                        for (int j = i + 1; j < count; j++) {
                            Particle ball = mBalls[j];
                            float dx = ball.mPosX - curr.mPosX;
                            float dy = ball.mPosY - curr.mPosY;
                            float dd = dx * dx + dy * dy;
                            // Check for collisions
                            if (dd <= sBallDiameter2) {
                                dx += ((float) Math.random() - 0.5f) * 0.0001f;
                                dy += ((float) Math.random() - 0.5f) * 0.0001f;
                                dd = dx * dx + dy * dy;
                                // simulate the spring
                                final float d = (float) Math.sqrt(dd);
                                final float c = (0.5f * (sBallDiameter - d))
                                        / d;
                                curr.mPosX -= dx * c;
                                curr.mPosY -= dy * c;
                                ball.mPosX += dx * c;
                                ball.mPosY += dy * c;
                                more = true;
                            }
                        }
                        curr.resolveCollisionWithBounds();
                    }
                }
            }

            public int getParticleCount() {
                return mBalls.length;
            }

            public float getPosX(int i) {
                return mBalls[i].mPosX;
            }

            public float getPosY(int i) {
                return mBalls[i].mPosY;
            }
        }

        public void startSimulation() {
            mSensorManager.registerListener(this, mAccelerometer,
                    SensorManager.SENSOR_DELAY_UI);
        }

        public void stopSimulation() { // 暂停时主要是停掉感应器
            mSensorManager.unregisterListener(this);
        }

        public SimulationView(Context context) {
            super(context);
            mAccelerometer = mSensorManager
                    .getDefaultSensor(Sensor.TYPE_ACCELEROMETER); // 实例化加速感应器
            DisplayMetrics metrics = new DisplayMetrics();
            getWindowManager().getDefaultDisplay().getMetrics(metrics); // 分辨率获取
            mXDpi = metrics.xdpi;
            mYDpi = metrics.ydpi;
            mMetersToPixelsX = mXDpi / 0.0254f;
            mMetersToPixelsY = mYDpi / 0.0254f;
            Bitmap ball = BitmapFactory.decodeResource(getResources(),
                    R.drawable.ball);
            final int dstWidth = (int) (sBallDiameter * mMetersToPixelsX + 0.5f);
            final int dstHeight = (int) (sBallDiameter * mMetersToPixelsY + 0.5f);
            mBitmap = Bitmap
                    .createScaledBitmap(ball, dstWidth, dstHeight, true); // 根据屏幕分辨率来设置素材的显示缩放比例
            Options opts = new Options();
            opts.inDither = true;
            opts.inPreferredConfig = Bitmap.Config.RGB_565;
            mWood = BitmapFactory.decodeResource(getResources(),
                    R.drawable.wood, opts);
        }

        @Override
        protected void onSizeChanged(int w, int h, int oldw, int oldh) { // 当View有变化时，Android123提示比如说横竖屏切换
            mXOrigin = (w - mBitmap.getWidth()) * 0.5f;
            mYOrigin = (h - mBitmap.getHeight()) * 0.5f;
            mHorizontalBound = ((w / mMetersToPixelsX - sBallDiameter) * 0.5f);
            mVerticalBound = ((h / mMetersToPixelsY - sBallDiameter) * 0.5f);
        }

        @Override
        public void onSensorChanged(SensorEvent event) { // 感应器数据有变化时
            if (event.sensor.getType() != Sensor.TYPE_ACCELEROMETER)
                return;
            switch (mDisplay.getRotation()) {
            case Surface.ROTATION_0:
                mSensorX = event.values[0];
                mSensorY = event.values[1];
                break;
            case Surface.ROTATION_90:
                mSensorX = -event.values[1];
                mSensorY = event.values[0];
                break;
            case Surface.ROTATION_180:
                mSensorX = -event.values[0];
                mSensorY = -event.values[1];
                break;
            case Surface.ROTATION_270:
                mSensorX = event.values[1];
                mSensorY = -event.values[0];
                break;
            }
            mSensorTimeStamp = event.timestamp;
            mCpuTimeStamp = System.nanoTime();
        }

        @Override
        protected void onDraw(Canvas canvas) { // 主要的小球绘制
            canvas.drawBitmap(mWood, 0, 0, null); // 先画出背景
            final ParticleSystem particleSystem = mParticleSystem;
            final long now = mSensorTimeStamp
                    + (System.nanoTime() - mCpuTimeStamp);
            final float sx = mSensorX;
            final float sy = mSensorY;
            particleSystem.update(sx, sy, now);
            final float xc = mXOrigin;
            final float yc = mYOrigin;
            final float xs = mMetersToPixelsX;
            final float ys = mMetersToPixelsY;
            final Bitmap bitmap = mBitmap;
            final int count = particleSystem.getParticleCount();
            for (int i = 0; i < count; i++) {
                final float x = xc + particleSystem.getPosX(i) * xs;
                final float y = yc - particleSystem.getPosY(i) * ys;
                canvas.drawBitmap(bitmap, x, y, null);
            }
            invalidate();
        }

        @Override
        public void onAccuracyChanged(Sensor sensor, int accuracy) {
        }
    }
}