#pragma once

namespace bg {
	class Info {
	public:
		Info() = default;
		~Info() = default;

		int32_t id = -1;
		std::string name = "";

		virtual void update(std::string prop, int32_t val);
		virtual void update(std::string prop, float val);
		virtual void update(std::string prop, std::string val);
	};
}

