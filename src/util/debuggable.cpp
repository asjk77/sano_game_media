#include <sano_game_media_pch.hpp>

namespace sg_media {
namespace util {

const char* ConvertDebuggableString(Debuggable* inDebuggable) {
  const char* debuggable_name = "Unknown";
  uint32_t debuggable_class_id =
      inDebuggable->GetDebuggableClassId();

  switch (debuggable_class_id) {
    case DebuggableClass::Debuggable:
      debuggable_name = "Debuggable";
      break;
    case DebuggableClass::Widget:
      debuggable_name = "DebuggableWidget";
      break;
    default:
      break;
  }
  return debuggable_name;
}

}  // namespace util
}  // namespace sg_media
