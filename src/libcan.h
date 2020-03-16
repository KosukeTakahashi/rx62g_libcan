/*
 * libcan.h
 *
 *  Created on: 2020/03/16
 *      Author: kosuke
 */

#ifndef LIBCAN_H_
#define LIBCAN_H_

namespace CAN {
	namespace PinSelection {
		enum Type {
			PB5_PB6 = 0,
			P23_P22 = 1,
			PE0_PD7 = 2
		};
	}

	namespace MailboxMode {
		enum Type {
			NORMAL = 0,
			FIFO   = 1
		};
	}

	namespace IDMode {
		enum Type {
			STANDARD_ONLY = 0,
			EXTENDED_ONLY = 1,
			MIXED         = 2
		};
	}

	namespace MsgLostMode {
		enum Type {
			OVERWRITE = 0,
			OVERRUN   = 1
		};
	}

	namespace MsgPriorityMode {
		enum Type {
			ID          = 0,
			MAILBOX_NUM = 1
		};
	}

	namespace TimestampPrescaler {
		enum Type {
			PER_1_BITTIME = 0,
			PER_2_BITTIME = 1,
			PER_4_BITTIME = 2,
			PER_8_BITTIME = 3
		};
	}

	namespace BusOffRecoveryMode {
		enum Type {
			BASED_ON_ISO_11898_1     = 0,
			HALT_ON_BUSOFF_START     = 1,
			HALT_ON_BUSOFF_END       = 2,
			HALT_ON_SOFTWARE_REQUEST = 3
		};
	}

	namespace Result {
		enum Type {
			OK      = 0,
			ERROR   = 1,
			INVALID = 2
		};
	}

	namespace OperationMode {
		enum Type {
			OPERATION   = 0,
			RESET       = 1,
			HALT        = 2,
			FORCE_RESET = 3
		};
	}

	namespace FrameType {
		enum Type {
			DATA_FRAME   = 0,
			REMOTE_FRAME = 1
		};
	}

	typedef struct {
		int id;
		unsigned char dlc;
		unsigned char data[8];
		FrameType::Type frameType;
	} Frame;

	class CANWrapper {
	public:
		CANWrapper();
		Result::Type setup(PinSelection::Type pinSelection,
						   MailboxMode::Type mbMode,
						   IDMode::Type idMode,
						   MsgLostMode::Type msgLostMode,
						   MsgPriorityMode::Type priorityMode,
						   TimestampPrescaler::Type prescaler,
						   BusOffRecoveryMode::Type recoveryMode,
						   int baudrate);
		Result::Type sleep(void);
		Result::Type wakeUp(void);
		Result::Type switchMode(OperationMode::Type mode);
		Result::Type loadMailbox(unsigned char mailbox, Frame frame);
		Result::Type transmitMailbox(unsigned char mailbox);
		Frame readMailbox(unsigned char mailbox);
	};

}
#endif /* LIBCAN_H_ */
