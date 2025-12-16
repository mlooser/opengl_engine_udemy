//
// Created by Marcin Lusa on 16/12/2025.
//

#include "Application.h"

void eng::Application::SetNeedsToBeClosed(bool needsToBeClosed) {
    this->needsToBeClosed = needsToBeClosed;
}

bool eng::Application::NeedsToBeClosed() const {
    return needsToBeClosed;
}
