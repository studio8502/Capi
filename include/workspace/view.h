/*
 ╔═══════════════════════════════════════════════════════════════════════════╗
 ║ workspace/view.h                                                          ║
 ╟───────────────────────────────────────────────────────────────────────────╢
 ║ Copyright © 2024 Kyle J Cardoza, Studio 8502 <Kyle.Cardoza@icloud.com>    ║
 ╟───────────────────────────────────────────────────────────────────────────╢
 ║ This program is free software: you can redistribute it and/or modify      ║
 ║ it under the terms of the GNU General Public License as published by      ║
 ║ the Free Software Foundation, either version 3 of the License, or         ║
 ║ (at your option) any later version.                                       ║
 ║                                                                           ║
 ║ This program is distributed in the hope that it will be useful,           ║
 ║ but WITHOUT ANY WARRANTY; without even the implied warranty of            ║
 ║ MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             ║
 ║ GNU General Public License for more details.                              ║
 ║                                                                           ║
 ║ You should have received a copy of the GNU General Public License         ║
 ║ along with this program.  If not, see <http://www.gnu.org/licenses/>.     ║
 ╚═══════════════════════════════════════════════════════════════════════════╝
 */

#pragma once

#include "capi.h"

#include "event_responder.h"

class View: public EventResponder {
public:

    enum LayoutConstraint: UInt8 {
        noResizing = 0,
        leftMarginStretch = 1,
        widthStretch = 2,
        rightMarginStretch = 4,
        bottomMarginStretch = 8,
        heightStretch = 16,
        topMarginStretch = 32
    };

    View();

    ~View();

    // Informs the parent that this view does or does not request
    // a tracking rect be placed to match its position and size rect.
    virtual method requestsTrackingRect() -> Bool;

    virtual method frame() -> Rect;

    virtual method setFrame(Rect frame) -> Void;

    // Adds a view as a subview.
    virtual method addSubview(View *subview) -> Void;

    virtual method removeSubview(View *subview) -> Void;

    virtual method draw() -> Void;

    virtual method resizeWithOldFrame(Rect oldFrame) -> Void;

    virtual method resizeSubviewsWithOldFrame(Rect oldFrame) -> Void;

    LayoutConstraint layout;

    Bool resizesSubviews;

    Rect _frame;

private:
    Window *_window;
    View *_superview;


    std::vector<View *> subviewList;
};
