/*
 * Copyright (C) 2011 The Android Open Source Project
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

/*
 * This file is auto-generated. DO NOT MODIFY!
 * The source Renderscript file: /Users/sijiewang/Documents/workspace/HelloWorld/src/com/example/android/rs/helloworld/helloworld.rs
 */
package com.example.android.rs.helloworld;

import android.renderscript.*;
import android.content.res.Resources;

/**
 * @hide
 */
public class ScriptC_helloworld extends ScriptC {
    // Constructor
    public  ScriptC_helloworld(RenderScript rs, Resources resources, int id) {
        super(rs, resources, id);
    }

    private final static int mExportVarIdx_gTouchX = 0;
    private int mExportVar_gTouchX;
    public void set_gTouchX(int v) {
        mExportVar_gTouchX = v;
        setVar(mExportVarIdx_gTouchX, v);
    }

    public int get_gTouchX() {
        return mExportVar_gTouchX;
    }

    private final static int mExportVarIdx_gTouchY = 1;
    private int mExportVar_gTouchY;
    public void set_gTouchY(int v) {
        mExportVar_gTouchY = v;
        setVar(mExportVarIdx_gTouchY, v);
    }

    public int get_gTouchY() {
        return mExportVar_gTouchY;
    }

}

