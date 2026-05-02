//Function overloading
class Time {
    int mHours, mMinutes, mSeconds; // private
public:
    // declaration lives inside the class
    friend Time operator+(Time& lhs, Time& rhs);
};

// definition lives outside — acts like a free function
// lhs = left hand side, rhs = right hand side
Time operator+(Time& lhs, Time& rhs) {
    // can access mHours, mMinutes, mSeconds because friend
}
----------------------------------------------------------------
