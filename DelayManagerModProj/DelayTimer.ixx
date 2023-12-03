module;
export module DelayTimer;
import std;

//includes some type aliases and a concept to make it single header, class DelayTimer
export namespace sds
{
	//using declarations, aliases
	namespace chron = std::chrono;
	using Nanos_t = chron::nanoseconds;
	using Clock_t = chron::steady_clock;
	using TimePoint_t = chron::time_point <Clock_t, Nanos_t>;

	//concept for DelayTimer or something usable as such.
	template<typename T>
	concept IsDelayTimer_c = requires(T & t)
	{
		{ T(std::chrono::seconds(1)) };
		{ t.IsElapsed() } -> std::convertible_to<bool>;
		{ t.Reset(std::chrono::seconds{ 5 }) };
		{ t.Reset() };
		{ t.GetTimerPeriod() } -> std::convertible_to<Nanos_t>;
		{ std::cout << t };
	};

	/**
	 * \brief	DelayManager manages a non-blocking time delay, it provides functions such as IsElapsed() and Reset(...)
	 */
	class DelayTimer final
	{
		TimePoint_t m_start_time{ Clock_t::now() };
		Nanos_t m_delayTime{}; // this should remain nanoseconds to ensure maximum granularity when Reset() with a different type.
		mutable bool m_has_fired{ false };
	public:
		DelayTimer() = delete;
		explicit DelayTimer(Nanos_t duration) noexcept : m_delayTime(duration) { }
		DelayTimer(const DelayTimer& other) = default;
		DelayTimer(DelayTimer&& other) = default;
		DelayTimer& operator=(const DelayTimer& other) = default;
		DelayTimer& operator=(DelayTimer&& other) = default;
		~DelayTimer() = default;
		/**
		 * \brief	Operator<< overload for ostream specialization, writes more detailed delay details for debugging.
		 */
		friend std::ostream& operator<<(std::ostream& os, const DelayTimer& obj) noexcept
		{
			os << "[DelayTimer]" << '\n'
				<< "m_start_time:" << obj.m_start_time.time_since_epoch() << '\n'
				<< "m_delayTime:" << obj.m_delayTime << '\n'
				<< "m_has_fired:" << obj.m_has_fired << '\n'
				<< "[/DelayTimer]";
			return os;
		}
		/**
		 * \brief	Check for elapsed.
		 * \return	true if timer has elapsed, false otherwise
		 */
		[[nodiscard]]
		bool IsElapsed() const noexcept
		{
			if (Clock_t::now() > (m_start_time + m_delayTime))
			{
				m_has_fired = true;
				return true;
			}
			return false;
		}
		/**
		 * \brief	Reset timer with chrono duration type.
		 * \param delay		Delay in nanoseconds (or any std::chrono duration type)
		 */
		void Reset(const Nanos_t delay) noexcept
		{
			m_start_time = Clock_t::now();
			m_has_fired = false;
			m_delayTime = { delay };
		}
		/**
		 * \brief	Reset timer to last used duration value for a new start point.
		 */
		void Reset() noexcept
		{
			m_start_time = Clock_t::now();
			m_has_fired = false;
		}
		/**
		 * \brief	Gets the current timer period/duration for elapsing.
		 */
		auto GetTimerPeriod() const
		{
			return m_delayTime;
		}
	};

}

