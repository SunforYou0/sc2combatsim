#pragma once

#include <sc2api/sc2_api.h>

#include <string>

namespace Util {
	struct POS_SQUAD {
		std::vector<sc2::UnitTypeID> unit_id;
		std::vector<int> num;
		std::vector<std::string> pos;
	};
	// Convert BGR image (24bpp) to RGB and save as .png
	void save_BGR_image(const std::string& filename, const char* imagedata, int32_t width, int32_t height);

	// Get filename timestring.
	std::string gettimestr();
	template <typename T>
	void vector_out(std::vector<T>& vec);
	std::tuple<std::vector<sc2::UnitTypeID>, std::vector<int>, std::vector<sc2::UnitTypeID>, std::vector<int> > ReadPresetSquad(const std::string& path);
	std::tuple<std::vector<sc2::UnitTypeID>, std::vector<int>, std::vector<std::string>, std::vector<sc2::UnitTypeID>, std::vector<int>, std::vector<std::string>>
		ReadPresetJSONSquad(const std::string& path);
	std::tuple<std::vector<std::string>, std::vector<POS_SQUAD>, std::vector<sc2::UnitTypeID>, std::vector<int>, std::vector<std::string>>
		ReadPresetJSONSquadWithTactic(const std::string& path);
	// Code from SC2CLIENT-API
	//! Determines if the unit matches the unit type.
	struct IsUnit {
		IsUnit(sc2::UNIT_TYPEID type) : type_(type) {};
		sc2::UNIT_TYPEID type_;
		bool operator()(const sc2::Unit& unit) { return unit.unit_type == type_; };
	};

	// Code from SC2CLIENT-API
	//! Determines if units matches the unit type.
	struct IsUnits {
		IsUnits(std::vector<sc2::UNIT_TYPEID> types) : types_(types) {};
		std::vector<sc2::UNIT_TYPEID> types_;
		bool operator()(const sc2::Unit& unit) {
			bool included = false;
			for (const auto& type : types_) {
				included = included || (unit.unit_type == type);
			}
			return included;
		};
	};
}