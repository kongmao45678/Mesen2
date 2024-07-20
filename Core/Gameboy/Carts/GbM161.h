#pragma once
#include "pch.h"
#include "Gameboy/Carts/GbCart.h"
#include "Gameboy/GbMemoryManager.h"
#include "Utilities/Serializer.h"

class GbM161 : public GbCart
{
private:
	uint8_t _prgBank = 0;

public:
	void InitCart() override
	{
		_memoryManager->MapRegisters(0x0000, 0x7FFF, RegisterAccess::Write);
	}

	void RefreshMappings() override
	{
		Map(0x0000, 0x7FFF, GbMemoryType::PrgRom, _prgBank * 0x8000, true);
	}

	void WriteRegister(uint16_t addr, uint8_t value) override
	{
		_prgBank = value & 0x0F;
		RefreshMappings();
		
		//Block all subsequent writes
		_memoryManager->MapRegisters(0x0000, 0x7FFF, RegisterAccess::None);
	}

	void Serialize(Serializer& s) override
	{
		SV(_prgBank);
	}
};