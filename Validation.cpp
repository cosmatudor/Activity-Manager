#include "Validation.h"

void Validation::validate(const Activity &activity) {
    string message = "";
    if (activity.getTitle().empty()) {
        message += "Invalid title!\n";
    }
    if (activity.getDescription().empty()) {
        message += "Invalid description!\n";
    }
    if (activity.getType().empty()) {
        message += "Invalid type!\n";
    }
    if (activity.getDuration() <= 0) {
        message += "Invalid duration!\n";
    }
    if (message.length() > 0) {
        throw ValidationException(message);
    }
}
