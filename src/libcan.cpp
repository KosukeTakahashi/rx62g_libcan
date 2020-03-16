/*
 * libcan.cpp
 *
 *  Created on: 2020/03/16
 *      Author: kosuke
 */

#include "libcan.h"
#include "iodefine.h"

using namespace CAN;

CANWrapper::CANWrapper(void) {}

Result::Type CANWrapper::setup(PinSelection::Type pinSelection,
							   MailboxMode::Type mbMode,
							   IDMode::Type idMode,
							   MsgLostMode::Type msgLostMode,
							   MsgPriorityMode::Type priorityMode,
							   TimestampPrescaler::Type prescaler,
							   BusOffRecoveryMode::Type recoveryMode,
							   int baudrate) {
	IOPORT.PFJCAN.BIT.CANE = 1;
	switch (pinSelection) {
	case PinSelection::PB5_PB6:
		IOPORT.PFJCAN.BIT.CANS = 0;
		PORTB.DR.BIT.B5 = 1;
		PORTB.ICR.BIT.B6 = 1;
		break;
	case PinSelection::P23_P22:
		IOPORT.PFJCAN.BIT.CANS = 1;
		PORT2.DR.BIT.B3 = 1;
		PORT2.ICR.BIT.B2 = 1;
		break;
	case PinSelection::PE0_PD7:
		IOPORT.PFJCAN.BIT.CANS = 2;
		PORTD.DR.BIT.B7 = 1;
		PORTE.ICR.BIT.B0 = 1;
		break;
	default:
		return Result::INVALID;
	}

	MSTP(CAN0);
	this->wakeUp();

	this->switchMode(OperationMode::RESET);

	switch (mbMode) {
	case MailboxMode::NORMAL:
		CAN0.CTLR.BIT.MBM = 0;
		break;
	case MailboxMode::FIFO:
		CAN0.CTLR.BIT.MBM = 1;
		break;
	}

	switch (idMode) {
	case IDMode::STANDARD_ONLY:
		CAN0.CTLR.BIT.IDFM = 0;
		break;
	case IDMode::EXTENDED_ONLY:
		CAN0.CTLR.BIT.IDFM = 1;
		break;
	case IDMode::MIXED:
		CAN0.CTLR.BIT.IDFM = 2;
		break;
	default:
		return Result::INVALID;
	}

	switch (msgLostMode) {
	case MsgLostMode::OVERWRITE:
		CAN0.CTLR.BIT.MLM = 0;
		break;
	case MsgLostMode::OVERRUN:
		CAN0.CTLR.BIT.MLM = 1;
		break;
	default:
		return Result::INVALID;
	}

	switch (priorityMode) {
	case MsgPriorityMode::ID:
		CAN0.CTLR.BIT.TPM = 0;
		break;
	case MsgPriorityMode::MAILBOX_NUM:
		CAN0.CTLR.BIT.TPM = 1;
		break;
	default:
		return Result::INVALID;
	}

	CAN0.CTLR.BIT.TSRC = 0;

	/*
	 * CAN0.CTLR.BIT.MBM = 0;
	CAN0.CTLR.BIT.IDFM = 2;
	CAN0.CTLR.BIT.MLM = 0;
	CAN0.CTLR.BIT.TPM = 0;
	CAN0.CTLR.BIT.TSRC = 0;
	CAN0.CTLR.BIT.TSPS = 3;
	CAN0.CTLR.BIT.BOM = 0;
	CAN0.CTLR.BIT.RBOC = 0;
	 */

	return Result::OK;
}

Result::Type CANWrapper::sleep(void) {
	return Result::OK;
}

Result::Type CANWrapper::wakeUp(void) {
	return Result::OK;
}

Result::Type CANWrapper::switchMode(OperationMode::Type mode) {
	return Result::OK;
}

Result::Type CANWrapper::loadMailbox(unsigned char mailbox, Frame frame) {
	return Result::OK;
}

Result::Type CANWrapper::transmitMailbox(unsigned char mailbox) {
	return Result::OK;
}

//Frame CANWrapper::readMailbox(unsigned char mailbox) {
//}
