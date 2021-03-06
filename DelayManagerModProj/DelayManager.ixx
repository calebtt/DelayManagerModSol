export module DelayManager;

import <ostream>;
import <chrono>;
import <syncstream>;

export namespace sds::Utilities
{
	/// <summary> C++20 modules DelayManager class, value is microseconds. </summary>
	class DelayManager
	{
		using ClockType = std::chrono::steady_clock;
		using TimeType = std::chrono::time_point<ClockType>;
		using DurationType = std::chrono::microseconds;

		TimeType m_start_time{ ClockType::now() };
		size_t m_duration{ 1 };
		bool m_has_fired{ false };
	public:
		//us is microseconds
		DelayManager() = delete;
		explicit DelayManager(size_t duration_us) : m_duration(duration_us) { }
		DelayManager(const DelayManager& other) = default;
		DelayManager(DelayManager&& other) = default;
		DelayManager& operator=(const DelayManager& other) = default;
		DelayManager& operator=(DelayManager&& other) = default;
		~DelayManager() = default;
		/// <summary>Operator<< overload for std::ostream specialization,
		///	writes more detailed delay details for debugging.
		///	Thread-safe, provided all writes to the ostream object
		///	are wrapped with std::osyncstream!</summary>
		friend std::ostream& operator<<(std::ostream& os, const DelayManager& obj) noexcept
		{
			std::osyncstream ss(os);
			ss << "[DelayManager]" << std::endl
				<< "m_start_time:" << obj.m_start_time.time_since_epoch() << std::endl
				<< "m_duration (microseconds):" << obj.m_duration << std::endl
				<< "m_has_fired:" << obj.m_has_fired << std::endl
				<< "[/DelayManager]";
			return os;
		}
		/// <summary>Check for elapsed.</summary>
		bool IsElapsed() noexcept
		{
			if (ClockType::now() > (m_start_time + DurationType(m_duration)))
			{
				m_has_fired = true;
				return true;
			}
			return false;
		}
		/// <summary>Reset delay for elapsing.</summary>
		void Reset(size_t microsec_delay) noexcept
		{
			m_start_time = ClockType::now();
			m_has_fired = false;
			m_duration = microsec_delay;
		}
	};
}
