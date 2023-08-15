/*
 * ap_io.hpp
 *
 *  Created on: 2023. 6. 10.
 *      Author: gns2l
 */

#ifndef AP__INC_AP_IO_HPP_
#define AP__INC_AP_IO_HPP_



#ifdef _USE_HW_RTOS
#define AP_IO_LOCK_BEGIN osMutexWait(ap_io_mutex_id, osWaitForever)
#define AP_IO_LOCK_END   osMutexRelease(ap_io_mutex_id)
#else
#define AP_IO_LOCK_BEGIN
#define AP_IO_LOCK_END
#endif




struct ap_io
{
#ifdef _USE_HW_RTOS
	osMutexId ap_io_mutex_id;
#endif

public:
	enum in_e// in_name
	{
		in_0x00 = AP_DEF_START_IN_ADDR,
		in_0x01,
		in_mode_key_manual,
		in_modde_key_auto,
		in_0x04,
		in_0x05,
		in_0x06,
		in_safety_sensor, //

		in_0x10, // reserved
		in_0x11,
		in_0x12,
		in_0x13,
		in_0x14,
		in_0x15,
		in_0x16,
		in_0x17,

		in_0x20, // ext_io 1
		in_0x21,
		in_0x22,
		in_0x23,
		in_0x24,
		in_0x25,
		in_0x26,
		in_0x27,

		in_0x30,
		in_0x31,
		in_0x32,
		in_0x33,
		in_0x34,
		in_0x35,
		in_0x36,
		in_0x37,

	};



	union in_u
	{
		volatile  uint32_t data{};
		struct
		{
			volatile unsigned in_0x00:1;
			volatile unsigned in_0x01:1;
			volatile unsigned in_mode_key_manual:1;
			volatile unsigned in_mode_key_auto:1;
			volatile unsigned in_0x04:1;
			volatile unsigned in_0x05:1;
			volatile unsigned in_0x06:1;
			volatile unsigned in_safety_sensor:1;

			volatile unsigned in_0x10:1;
			volatile unsigned in_0x11:1;
			volatile unsigned in_0x12:1;
			volatile unsigned in_0x13:1;
			volatile unsigned in_0x14:1;
			volatile unsigned in_0x15:1;
			volatile unsigned in_0x16:1;
			volatile unsigned in_0x17:1;

			volatile unsigned in_0x20:1;
			volatile unsigned in_0x21:1;
			volatile unsigned in_0x22:1;
			volatile unsigned in_0x23:1;
			volatile unsigned in_0x24:1;
			volatile unsigned in_0x25:1;
			volatile unsigned in_0x26:1;
			volatile unsigned in_0x27:1;

			volatile unsigned in_0x30:1;
			volatile unsigned in_0x31:1;
			volatile unsigned in_0x32:1;
			volatile unsigned in_0x33:1;
			volatile unsigned in_0x34:1;
			volatile unsigned in_0x35:1;
			volatile unsigned in_0x36:1;
			volatile unsigned in_0x37:1;
		};
	};

	enum out_e//out_name
	{
		out_0x00 = AP_DEF_START_OUT_ADDR,
				out_0x01,
				out_0x02,
				out_0x03,
				out_0x04,
				out_0x05,
				out_0x06,
				out_0x07,

				out_0x10, // reserved
				out_0x11,
				out_0x12,
				out_0x13,
				out_0x14,
				out_0x15,
				out_0x16,
				out_0x17,

				out_0x20, // ext_io 1
				out_0x21,
				out_0x22,
				out_0x23,
				out_0x24,
				out_0x25,
				out_0x26,
				out_0x27,

				out_0x30,
				out_0x31,
				out_0x32,
				out_0x33,
				out_0x34,
				out_0x35,
				out_0x36,
				out_0x37,
	};
	// 1bank 4byte
	union out_u
	{
		volatile  uint32_t data{};
		struct
		{
			volatile unsigned out_0x00:1;
			volatile unsigned out_0x01:1;
			volatile unsigned out_0x02:1;
			volatile unsigned out_0x03:1;
			volatile unsigned out_0x04:1;
			volatile unsigned out_0x05:1;
			volatile unsigned out_0x06:1;
			volatile unsigned out_0x07:1;

			volatile unsigned out_0x10:1;
			volatile unsigned out_0x11:1;
			volatile unsigned out_0x12:1;
			volatile unsigned out_0x13:1;
			volatile unsigned out_0x14:1;
			volatile unsigned out_0x15:1;
			volatile unsigned out_0x16:1;
			volatile unsigned out_0x17:1;

			volatile unsigned out_0x20:1;
			volatile unsigned out_0x21:1;
			volatile unsigned out_0x22:1;
			volatile unsigned out_0x23:1;
			volatile unsigned out_0x24:1;
			volatile unsigned out_0x25:1;
			volatile unsigned out_0x26:1;
			volatile unsigned out_0x27:1;

			volatile unsigned out_0x30:1;
			volatile unsigned out_0x31:1;
			volatile unsigned out_0x32:1;
			volatile unsigned out_0x33:1;
			volatile unsigned out_0x34:1;
			volatile unsigned out_0x35:1;
			volatile unsigned out_0x36:1;
			volatile unsigned out_0x37:1;
		};
	};

	union sysio_u
	{
		uint16_t system_io{};
		struct
		{
			volatile unsigned start_sw:1;
			volatile unsigned stop_sw:1;
			volatile unsigned reset_sw:1;
			volatile unsigned estop_Sw:1;
			volatile unsigned in_0x04:1;
			volatile unsigned in_0x05:1;
			volatile unsigned in_0x06:1;
			volatile unsigned in_0x07:1;

			volatile unsigned start_lamp:1;
			volatile unsigned stop_lamp:1;
			volatile unsigned reset_lamp:1;
			volatile unsigned out_0x03:1;
			volatile unsigned out_0x04:1;
			volatile unsigned out_0x05:1;
			volatile unsigned out_0x06:1;
			volatile unsigned out_0x07:1;

		};
	};



	volatile in_u m_in;
	volatile out_u m_out;
	volatile sysio_u m_sysio;
	//volatile uint16_t m_extIn;
	//volatile uint16_t m_extOut;

	uint8_t m_errCnt;
public:
	ap_io() : m_in{}, m_out{} ,m_sysio{}/*, m_extIn{0}, m_extOut{0}*/ ,m_errCnt{}{
#ifdef _USE_HW_RTOS
		osMutexDef(ap_io_mutex_id);
		ap_io_mutex_id = osMutexCreate (osMutex(ap_io_mutex_id));
#endif
	}
	virtual ~ap_io(){}

	inline int Init(){
		//pca8575pw_Read(_PCA8575PW_EX_IO_CH_OUT, (uint16_t*)&m_extOut);
		LOG_PRINT("Init Success!");
		return ERROR_SUCCESS;
	}

	/*inline void assignObj(iio* p_io){
    pIo = p_io;
 }*/

	//Update information that has changed compared to previous data
	inline void SetOutputReg(uint32_t reg, uint8_t bank = 0)
	{
		uint32_t x_reg = reg ^ m_out.data;

		for(uint8_t i = 0 ; i < 32; i++)
		{
			if((x_reg >>(i))&1)
			{
				SetGpioOut((out_e)(i+AP_DEF_START_OUT_ADDR),((reg>>(i))&1));
			}
		}
	}

	inline int SetGpioOut(out_e out_idx, bool onoff = true){
		if ((uint32_t)out_idx < AP_DEF_START_OUT_ADDR)
			return -1;

		AP_IO_LOCK_BEGIN;
		GPIO_PinState state = onoff?GPIO_OUT_STATE_ON:GPIO_OUT_STATE_OFF;


		switch (out_idx)
		{
		case out_0x00:
			HAL_GPIO_WritePin(OUT_0_GPIO_Port, OUT_0_Pin, state);
			break;
		case out_0x01:
			HAL_GPIO_WritePin(OUT_1_GPIO_Port, OUT_1_Pin,state);
			break;
		case out_0x02:
			HAL_GPIO_WritePin(OUT_2_GPIO_Port, OUT_2_Pin,state);
			break;
		case out_0x03:
			HAL_GPIO_WritePin(OUT_3_GPIO_Port, OUT_3_Pin,state);
			break;
		case out_0x04:
			HAL_GPIO_WritePin(OUT_4_GPIO_Port, OUT_4_Pin,state);
			break;
		case out_0x05:
			HAL_GPIO_WritePin(OUT_5_GPIO_Port, OUT_5_Pin,state);
			break;
		case out_0x06:
			HAL_GPIO_WritePin(OUT_6_GPIO_Port, OUT_6_Pin,state);
			break;
		case out_0x07:
			HAL_GPIO_WritePin(OUT_7_GPIO_Port, OUT_7_Pin,state);
			break;
		case out_0x10:
			HAL_GPIO_WritePin(OUT_8_GPIO_Port, OUT_8_Pin,state);
			break;
		case out_0x11:
			HAL_GPIO_WritePin(OUT_9_GPIO_Port, OUT_9_Pin,state);
			break;
		case out_0x12:
			HAL_GPIO_WritePin(OUT_10_GPIO_Port, OUT_10_Pin,state);
			break;
		case out_0x13:
			HAL_GPIO_WritePin(OUT_11_GPIO_Port, OUT_11_Pin,state);
			break;
		case out_0x14:
			HAL_GPIO_WritePin(OUT_12_GPIO_Port, OUT_12_Pin,state);
			break;
		case out_0x15:
			HAL_GPIO_WritePin(OUT_13_GPIO_Port, OUT_13_Pin,state);
			break;
		case out_0x16:
			HAL_GPIO_WritePin(OUT_14_GPIO_Port, OUT_14_Pin,state);
			break;
		case out_0x17:
			HAL_GPIO_WritePin(OUT_15_GPIO_Port, OUT_15_Pin,state);
			break;
		default:
			return -1;
		}
		// end of switch

		AP_IO_LOCK_END;
		return ERROR_SUCCESS;
	}


	inline void Update_io(void){
		enum Bank { b1, b2, b3, b4, b_max };
		std::array<uint8_t, b_max> datas {};

		auto in_state = [](auto state) -> uint8_t{
			return (state == GPIO_IN_STATE_ON) ? 1 : 0;
		};

		uint8_t gpio{};
		// Out
		{
			gpio |= (uint8_t)HAL_GPIO_ReadPin(OUT_0_GPIO_Port, OUT_0_Pin) << 0;
			gpio |= (uint8_t)HAL_GPIO_ReadPin(OUT_1_GPIO_Port, OUT_1_Pin) << 1;
			gpio |= (uint8_t)HAL_GPIO_ReadPin(OUT_2_GPIO_Port, OUT_2_Pin) << 2;
			gpio |= (uint8_t)HAL_GPIO_ReadPin(OUT_3_GPIO_Port, OUT_3_Pin) << 3;
			gpio |= (uint8_t)HAL_GPIO_ReadPin(OUT_4_GPIO_Port, OUT_4_Pin) << 4;
			gpio |= (uint8_t)HAL_GPIO_ReadPin(OUT_5_GPIO_Port, OUT_5_Pin) << 5;
			gpio |= (uint8_t)HAL_GPIO_ReadPin(OUT_6_GPIO_Port, OUT_6_Pin) << 6;
			gpio |= (uint8_t)HAL_GPIO_ReadPin(OUT_7_GPIO_Port, OUT_7_Pin) << 7;
			datas[b1] = gpio;
			gpio = 0;
			gpio |= (uint8_t)HAL_GPIO_ReadPin(OUT_8_GPIO_Port, OUT_8_Pin) << 0;
			gpio |= (uint8_t)HAL_GPIO_ReadPin(OUT_9_GPIO_Port, OUT_9_Pin) << 1;
			gpio |= (uint8_t)HAL_GPIO_ReadPin(OUT_10_GPIO_Port, OUT_10_Pin) << 2;
			gpio |= (uint8_t)HAL_GPIO_ReadPin(OUT_11_GPIO_Port, OUT_11_Pin) << 3;
			gpio |= (uint8_t)HAL_GPIO_ReadPin(OUT_12_GPIO_Port, OUT_12_Pin) << 4;
			gpio |= (uint8_t)HAL_GPIO_ReadPin(OUT_13_GPIO_Port, OUT_13_Pin) << 5;
			gpio |= (uint8_t)HAL_GPIO_ReadPin(OUT_14_GPIO_Port, OUT_14_Pin) << 6;
			gpio |= (uint8_t)HAL_GPIO_ReadPin(OUT_15_GPIO_Port, OUT_15_Pin) << 7;
			datas[b1] = gpio;

			datas[b3] = 0;
			datas[b4] = 0;
			m_out.data = *(reinterpret_cast<uint32_t *>(datas.data()));

			// Extension IO module

		}

		// In
		{
			datas.fill(0);
			gpio = 0;
			gpio |= in_state(HAL_GPIO_ReadPin(IN_0_GPIO_Port, IN_0_Pin)) << 0;
			gpio |= in_state(HAL_GPIO_ReadPin(IN_1_GPIO_Port, IN_1_Pin)) << 1;
			gpio |= in_state(HAL_GPIO_ReadPin(IN_2_GPIO_Port, IN_2_Pin)) << 2;
			gpio |= in_state(HAL_GPIO_ReadPin(IN_3_GPIO_Port, IN_3_Pin)) << 3;
			gpio |= in_state(HAL_GPIO_ReadPin(IN_4_GPIO_Port, IN_4_Pin)) << 4;
			gpio |= in_state(HAL_GPIO_ReadPin(IN_5_GPIO_Port, IN_5_Pin)) << 5;
			gpio |= in_state(HAL_GPIO_ReadPin(IN_6_GPIO_Port, IN_6_Pin)) << 6;
			gpio |= in_state(HAL_GPIO_ReadPin(IN_7_GPIO_Port, IN_7_Pin)) << 7;
			datas[b1] = gpio;

			gpio = 0;
			gpio |= in_state(HAL_GPIO_ReadPin(IN_8_GPIO_Port, IN_8_Pin)) << 0;
			gpio |= in_state(HAL_GPIO_ReadPin(IN_9_GPIO_Port, IN_9_Pin)) << 1;
			gpio |= in_state(HAL_GPIO_ReadPin(IN_10_GPIO_Port, IN_10_Pin)) << 2;
			gpio |= in_state(HAL_GPIO_ReadPin(IN_11_GPIO_Port, IN_11_Pin)) << 3;
			gpio |= in_state(HAL_GPIO_ReadPin(IN_12_GPIO_Port, IN_12_Pin)) << 4;
			gpio |= in_state(HAL_GPIO_ReadPin(IN_13_GPIO_Port, IN_13_Pin)) << 5;
			gpio |= in_state(HAL_GPIO_ReadPin(IN_14_GPIO_Port, IN_14_Pin)) << 6;
			gpio |= in_state(HAL_GPIO_ReadPin(IN_15_GPIO_Port, IN_15_Pin)) << 7;
			datas[b2] = gpio;


			datas[b3] = 0;
			datas[b4] = 0;


			m_in.data = *(reinterpret_cast<uint32_t *>(datas.data()));
		}


		AP_IO_LOCK_END;
	}



	/* IO  control function */
	inline bool IsOn(uint32_t addr) {
		Update_io();

		if (addr < AP_DEF_START_OUT_ADDR) // Input
			return (m_in.data >> (addr - AP_DEF_START_IN_ADDR)) & 1;
		else // Output
			return (m_out.data >> (addr - AP_DEF_START_OUT_ADDR)) & 1;
	}

	inline bool IsOff(uint32_t addr) {
		return !IsOn(addr);
	}

	inline int OutputOn(uint32_t addr) {
		return SetGpioOut((out_e)addr);
	}

	inline int OutputOff(uint32_t addr) {
		return SetGpioOut((out_e)addr, false);
	}

	inline int OutputToggle(uint32_t addr){
		int ret = ERROR_SUCCESS;
		if (IsOn(addr))
			ret = OutputOff(addr);
		else
			ret = OutputOn(addr);
		return ret;
	}


};


#endif /* AP__INC_AP_IO_HPP_ */
