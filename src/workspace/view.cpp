/*****************************************************************************
 ╔═══════════════════════════════════════════════════════════════════════════╗
 ║ workspace/view.cpp                                                        ║
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
 ****************************************************************************/

#include "workspace/view.h"


View::View():
    layout(noResizing),
    resizesSubviews(false),
    _frame(0,0,100,100),
    surface(make_shared<Surface>(_frame.size(), _frame.origin())),
    _window(nullptr),
    _superview(nullptr),
    subviewList()
{}

View::~View() {}

method View::requestsTrackingRect() -> Bool {
    return false;
}

method View::frame() -> Rect {
    return _frame;
}

method View::setFrame(Rect frame) -> Void {
    var oldFrame = _frame;
    _frame = frame;

    surface.reset();
    surface = make_shared<Surface>(_frame.width, _frame.height);

    if (resizesSubviews == true) {
        resizeSubviewsWithOldFrame(oldFrame);
    }
}

method View::addSubview(View *subview) -> Void {
    subviewList.push_back(subview);
}

method View::removeSubview(View *subview) -> Void {
    std::erase_if(subviewList, [subview](var view){
        return subview == view;
    });
}

// Adapted from an old version of GNUstep-GUI
method View::resizeWithOldFrame(Rect oldFrame) -> Void {
    guard (layout != noResizing) else {
        return;
    }
    
    var superviewFrame = Rect(0,0,0,0);
    var newFrame = _frame;
  
    if (_superview != nullptr) {
        superviewFrame = _superview->frame();
    }

    Int options = 0;

    // Determine if and how the X axis can be resized
    if (layout & widthStretch) {
        options += 1;
    }

    if (layout & leftMarginStretch) {
        options += 1;
    }

    if (layout & rightMarginStretch) {
        options += 1;
    }

    // Adjust the X axis if any X options are set in the layout

    if (options > 0) {
        Int16 change = superviewFrame.width - oldFrame.width;
        Int16 changePerOption = change / options;

        if (layout & widthStretch) {
            newFrame.width += changePerOption;
        }

        if (layout & leftMarginStretch) {
            newFrame.x += changePerOption;
        }
    }

    options = 0;

    // Determine if and how the Y axis can be resized

    if (layout & heightStretch) {
        options += 1;
    }

    if (layout & topMarginStretch) {
        options += 1;
    }

    if (layout & bottomMarginStretch) {
        options += 1;
    }

    // Adjust the Y axis if any Y options are set in the mask

    if (options > 0) {
        Int16 change = superviewFrame.height - oldFrame.height;
        Int16 changePerOption = change / options;

        if (layout & heightStretch) {
            newFrame.height += changePerOption;
        }

        if (layout & topMarginStretch) {
            newFrame.y += changePerOption;
        }
    }

    setFrame(newFrame);

}

method View::resizeSubviewsWithOldFrame(Rect oldFrame) -> Void {
    for (var view : subviewList) {
        guard (view != nullptr) else { continue; }
        view->resizeWithOldFrame(oldFrame);
    }
}

method View::draw() -> Void {

    surface->setFillColor(0xFFFFFFFF);
    surface->fillRect(Rect(0, 0, _frame.width, _frame.height));

    surface->render();

    for (var view : subviewList) {
        guard (view != nullptr) else { continue; }
        view->draw();
        surface->drawSurface(view->surface, view->frame().origin());
    }
}
