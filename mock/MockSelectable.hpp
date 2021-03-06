#include <gmock-wrapper.h>
// Import GMock first because of F macro collisions
#include <Selectors/Selectable.hpp>

#if __GNUC__ >= 5
// Disable GCC 5's -Wsuggest-override warnings in mock methods
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wsuggest-override"
#endif

template <setting_t N>
class MockSelectable : public Selectable<N> {
  public:
    MOCK_METHOD1(select, void(setting_t));
};

#if __GNUC__ >= 5
# pragma GCC diagnostic pop
#endif