/*
 * Copyright (C) 2014 The Android Open Source Project
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

package com.android.inputmethod.accessibility;

import android.view.MotionEvent;

import com.android.inputmethod.keyboard.KeyDetector;
import com.android.inputmethod.keyboard.MoreKeysKeyboardView;

public final class MoreSuggestionsAccessibilityDelegate
        extends MoreKeysKeyboardAccessibilityDelegate {
    public MoreSuggestionsAccessibilityDelegate(final MoreKeysKeyboardView moreKeysKeyboardView,
            final KeyDetector keyDetector) {
        super(moreKeysKeyboardView, keyDetector);
    }

    // TODO: Remove redundant override method.
    @Override
    protected void simulateTouchEvent(final int touchAction, final MotionEvent hoverEvent) {
        final MotionEvent touchEvent = MotionEvent.obtain(hoverEvent);
        touchEvent.setAction(touchAction);
        mKeyboardView.onTouchEvent(touchEvent);
        touchEvent.recycle();
    }
}