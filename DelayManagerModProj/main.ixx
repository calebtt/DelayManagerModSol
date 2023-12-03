import std;
import DelayTimer;

/* C++20 modules main example. */
int main()
{
	using namespace std::chrono_literals;
	namespace chron = std::chrono;
	constexpr auto DelayValue = 5s;
	constexpr auto LoopDelay = 1s;

	sds::DelayTimer delayTimer(DelayValue);
	while (!delayTimer.IsElapsed())
	{
		std::cout << "\nStill waiting...\n";
		std::cout << delayTimer << '\n'; // print some debug info
		std::this_thread::sleep_for(chron::microseconds(LoopDelay));
	}
	std::cout << "Done...";
}