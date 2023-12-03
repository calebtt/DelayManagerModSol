import std;
import DelayManager;

/* C++20 modules main example. */
int main()
{
	namespace chron = std::chrono;
	namespace util = sds::Utilities;
	// five million microsecs (5 seconds)
	constexpr size_t DelayValue = 5 * 1'000'000;
	// microsecs (1 sec)
	constexpr size_t LoopDelay = 1'000'000;

	util::DelayManager dm(DelayValue);
	while (!dm.IsElapsed())
	{
		std::cout << "\nStill waiting...\n";
		std::cout << dm << '\n'; // print some debug info
		std::this_thread::sleep_for(chron::microseconds(LoopDelay));
	}
	std::cout << "Done...";
}