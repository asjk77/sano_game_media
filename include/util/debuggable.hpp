
/**
 * NOTE Enum class 를 사용하고 싶지만 상속이 불가능하여 이 것을 이용함 
 *
 */
class DebuggableClass {
public:
    enum {
        Start = 0,
        Debuggable,
        Widget,
        End
    };
};

#define SN_DEBUGGABLE_CLASS_IDENTIFIER_SUPER(c) \
  SN_CLASS_IDENTIFIER_SUPER(DebuggableClass, c)

#define SN_DEBUGGABLE_CLASS_IDENTIFIER_SUB(c) \
  SN_CLASS_IDENTIFIER_SUB(DebuggableClass, c)
/**
 * @brief 만약 디버그 가능한 객체일 경우 해당 위젯을 상속받습니다.
 */
class Debuggable {
 public:
  SN_DEBUGGABLE_CLASS_IDENTIFIER_SUPER(DebuggableClass::Debuggable)

 private:
};

class DebuggableWidget : public Debuggable {
 public:
  SN_DEBUGGABLE_CLASS_IDENTIFIER_SUB(DebuggableClass::Widget)

 private:
};

const char* ConvertDebuggableString(Debuggable* inDebuggable);

/**
 * @brief 실제 객체로 바꿉니다.
 *
 * @tparam T
 * @param inDebuggable
 *
 * @return 만약 실패시 nullptr 성공시 해당 객체
 */
template <typename T>
T* ConvertDebuggable(Debuggable* inDebuggable) {
  static_assert(std::is_base_of<Debuggable, T>::value,
                "Debuggable 를 상속 받아야 합니다.");

  if (inDebuggable->GetDebuggableClassId() != T::DebuggableClassId)
    return nullptr;

  return static_cast<T*>(inDebuggable);
}
