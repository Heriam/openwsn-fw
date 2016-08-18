#include "opendefs.h"
#include "schedule.h"
#include "openserial.h"
#include "openrandom.h"
#include "packetfunctions.h"
#include "sixtop.h"
#include "idmanager.h"

//=========================== variables =======================================
schedule_vars_t schedule_vars;

//=========================== prototypes ======================================

void schedule_resetEntry(scheduleEntry_t* pScheduleEntry);

//=========================== public ==========================================

//=== admin

/**
\brief Initialize this module.

\post Call this function before calling any other function in this module.
*/
void schedule_init() {
	slotOffset_t    start_slotOffset;
	slotOffset_t    running_slotOffset;
	open_addr_t     temp_neighbor;

	// reset local variables


	memset(&schedule_vars,0,sizeof (schedule_vars_t));
	for (running_slotOffset=0;running_slotOffset<MAXACTIVESLOTS;running_slotOffset++) {
		schedule_resetEntry(&schedule_vars.scheduleBuf[running_slotOffset]);
	}
	schedule_vars.backoffExponent = MINBE-1;
	schedule_vars.maxActiveSlots = MAXACTIVESLOTS;

	start_slotOffset = SCHEDULE_MINIMAL_6TISCH_SLOTOFFSET;
	if (idmanager_getIsDAGroot()==TRUE) {
		schedule_startDAGroot();
	}

	// serial RX slot(s)
	start_slotOffset += SCHEDULE_MINIMAL_6TISCH_ACTIVE_CELLS;
	memset(&temp_neighbor,0,sizeof(temp_neighbor));
	for (running_slotOffset=start_slotOffset;running_slotOffset<start_slotOffset+15;running_slotOffset++) {
		schedule_addActiveSlot(
				running_slotOffset,                    // slot offset
				CELLTYPE_SERIALRX,                     // type of slot
				FALSE,                                 // shared?
				0,                                     // channel offset
				&temp_neighbor,                        // neighbor
				0,										// trackID
				0,										// bundleID
				FALSE                                  // bier
		);
	}

	// hardcoded BIER slots :
	temp_neighbor.type = ADDR_ANYCAST;
	switch (idmanager_getMyID(ADDR_64B)->addr_64b[7]) {
	case 0xd9 :
		schedule_addActiveSlot(
				17,                   // slot offset
				CELLTYPE_TX,                  		  // type of slot
				FALSE,                                // shared?
				0,                                    // channel offset
				&temp_neighbor,                       // neighbor
				1,									  // track ID
				0,									  // bierbitindex
				TRUE
		);
		schedule_addActiveSlot(
				23,                   // slot offset
				CELLTYPE_TX,                  		  // type of slot
				FALSE,                                // shared?
				0,                                    // channel offset
				&temp_neighbor,                       // neighbor
				4,									  // track ID
				0,									  // bierbitindex
				TRUE
		);
			schedule_addActiveSlot(
					30,                   // slot offset
					CELLTYPE_TX,                  		  // type of slot
					FALSE,                                // shared?
					0,                                    // channel offset
					&temp_neighbor,                       // neighbor
					5,									  // track ID
					0,									  // bierbitindex
					TRUE
			);
			schedule_addActiveSlot(
					31,                   // slot offset
					CELLTYPE_TX,                  		  // type of slot
					FALSE,                                // shared?
					1,                                    // channel offset
					&temp_neighbor,                       // neighbor
					5,									  // track ID
					1,									  // bierbitindex
					TRUE
			);
			schedule_addActiveSlot(
					45,                   // slot offset
					CELLTYPE_TX,                  		  // type of slot
					FALSE,                                // shared?
					0,                                    // channel offset
					&temp_neighbor,                       // neighbor
					6,									  // track ID
					0,									  // bierbitindex
					TRUE
			);
		break;
	case 0x4a :
		schedule_addActiveSlot(
				17,                   // slot offset
				CELLTYPE_RX,                  		  // type of slot
				FALSE,                                // shared?
				0,                                    // channel offset
				&temp_neighbor,                       // neighbor
				1,									  // track ID
				0,									  // bierbitindex
				TRUE
		);
		schedule_addActiveSlot(
				18,                   // slot offset
				CELLTYPE_TX,                  		  // type of slot
				FALSE,                                // shared?
				1,                                    // channel offset
				&temp_neighbor,                       // neighbor
				1,									  // track ID
				1,									  // bierbitindex
				TRUE
		);
			schedule_addActiveSlot(
					23,                   // slot offset
					CELLTYPE_RX,                  		  // type of slot
					FALSE,                                // shared?
					0,                                    // channel offset
					&temp_neighbor,                       // neighbor
					4,									  // track ID
					0,									  // bierbitindex
					TRUE
			);
			schedule_addActiveSlot(
					24,                   // slot offset
					CELLTYPE_TX,                  		  // type of slot
					FALSE,                                // shared?
					1,                                    // channel offset
					&temp_neighbor,                       // neighbor
					4,									  // track ID
					1,									  // bierbitindex
					TRUE
			);
			schedule_addActiveSlot(
					30,                   // slot offset
					CELLTYPE_RX,                  		  // type of slot
					FALSE,                                // shared?
					0,                                    // channel offset
					&temp_neighbor,                       // neighbor
					5,									  // track ID
					0,									  // bierbitindex
					TRUE
			);
			schedule_addActiveSlot(
					32,                   // slot offset
					CELLTYPE_TX,                  		  // type of slot
					FALSE,                                // shared?
					2,                                    // channel offset
					&temp_neighbor,                       // neighbor
					5,									  // track ID
					2,									  // bierbitindex
					TRUE
			);
			schedule_addActiveSlot(
					33,                   // slot offset
					CELLTYPE_RX,                  		  // type of slot
					FALSE,                                // shared?
					3,                                    // channel offset
					&temp_neighbor,                       // neighbor
					5,									  // track ID
					2,									  // bierbitindex
					TRUE
			);
			schedule_addActiveSlot(
					34,                   // slot offset
					CELLTYPE_TX,                  		  // type of slot
					FALSE,                                // shared?
					4,                                    // channel offset
					&temp_neighbor,                       // neighbor
					5,									  // track ID
					3,									  // bierbitindex
					TRUE
			);
			schedule_addActiveSlot(
					45,                   // slot offset
					CELLTYPE_RX,                  		  // type of slot
					FALSE,                                // shared?
					0,                                    // channel offset
					&temp_neighbor,                       // neighbor
					6,									  // track ID
					0,									  // bierbitindex
					TRUE
			);
			schedule_addActiveSlot(
					46,                   // slot offset
					CELLTYPE_TX,                  		  // type of slot
					FALSE,                                // shared?
					1,                                    // channel offset
					&temp_neighbor,                       // neighbor
					6,									  // track ID
					1,									  // bierbitindex
					TRUE
			);
			schedule_addActiveSlot(
					47,                   // slot offset
					CELLTYPE_RX,                  		  // type of slot
					FALSE,                                // shared?
					2,                                    // channel offset
					&temp_neighbor,                       // neighbor
					6,									  // track ID
					1,									  // bierbitindex
					TRUE
			);
			schedule_addActiveSlot(
					48,                   // slot offset
					CELLTYPE_TX,                  		  // type of slot
					FALSE,                                // shared?
					3,                                    // channel offset
					&temp_neighbor,                       // neighbor
					6,									  // track ID
					2,									  // bierbitindex
					TRUE
			);
		break;
	case 0x02 :
		schedule_addActiveSlot(
				17,                   // slot offset
				CELLTYPE_RX,                  		  // type of slot
				FALSE,                                // shared?
				0,                                    // channel offset
				&temp_neighbor,                       // neighbor
				1,									  // track ID
				0,									  // bierbitindex
				TRUE
		);
		schedule_addActiveSlot(
				18,                   // slot offset
				CELLTYPE_TX,                  		  // type of slot
				FALSE,                                // shared?
				2,                                    // channel offset
				&temp_neighbor,                       // neighbor
				1,									  // track ID
				2,									  // bierbitindex
				TRUE
		);
			schedule_addActiveSlot(
					23,                   // slot offset
					CELLTYPE_RX,                  		  // type of slot
					FALSE,                                // shared?
					0,                                    // channel offset
					&temp_neighbor,                       // neighbor
					4,									  // track ID
					0,									  // bierbitindex
					TRUE
			);
			schedule_addActiveSlot(
					25,                   // slot offset
					CELLTYPE_TX,                  		  // type of slot
					FALSE,                                // shared?
					2,                                    // channel offset
					&temp_neighbor,                       // neighbor
					4,									  // track ID
					2,									  // bierbitindex
					TRUE
			);
			schedule_addActiveSlot(
					31,                   // slot offset
					CELLTYPE_RX,                  		  // type of slot
					FALSE,                                // shared?
					1,                                    // channel offset
					&temp_neighbor,                       // neighbor
					5,									  // track ID
					1,									  // bierbitindex
					TRUE
			);
			schedule_addActiveSlot(
					32,                   // slot offset
					CELLTYPE_RX,                  		  // type of slot
					FALSE,                                // shared?
					2,                                    // channel offset
					&temp_neighbor,                       // neighbor
					5,									  // track ID
					2,									  // bierbitindex
					TRUE
			);
			schedule_addActiveSlot(
					33,                   // slot offset
					CELLTYPE_TX,                  		  // type of slot
					FALSE,                                // shared?
					3,                                    // channel offset
					&temp_neighbor,                       // neighbor
					5,									  // track ID
					2,									  // bierbitindex
					TRUE
			);
			schedule_addActiveSlot(
					35,                   // slot offset
					CELLTYPE_TX,                  		  // type of slot
					FALSE,                                // shared?
					5,                                    // channel offset
					&temp_neighbor,                       // neighbor
					5,									  // track ID
					4,									  // bierbitindex
					TRUE
			);
			schedule_addActiveSlot(
					45,                   // slot offset
					CELLTYPE_RX,                  		  // type of slot
					FALSE,                                // shared?
					0,                                    // channel offset
					&temp_neighbor,                       // neighbor
					6,									  // track ID
					0,									  // bierbitindex
					TRUE
			);
			schedule_addActiveSlot(
					46,                   // slot offset
					CELLTYPE_RX,                  		  // type of slot
					FALSE,                                // shared?
					1,                                    // channel offset
					&temp_neighbor,                       // neighbor
					6,									  // track ID
					1,									  // bierbitindex
					TRUE
			);
			schedule_addActiveSlot(
					47,                   // slot offset
					CELLTYPE_TX,                  		  // type of slot
					FALSE,                                // shared?
					2,                                    // channel offset
					&temp_neighbor,                       // neighbor
					6,									  // track ID
					1,									  // bierbitindex
					TRUE
			);
			schedule_addActiveSlot(
					48,                   // slot offset
					CELLTYPE_TX,                  		  // type of slot
					FALSE,                                // shared?
					4,                                    // channel offset
					&temp_neighbor,                       // neighbor
					6,									  // track ID
					3,									  // bierbitindex
					TRUE
			);
		break;
	case 0xd8 :
		schedule_addActiveSlot(
				18,                   // slot offset
				CELLTYPE_RX,                  		  // type of slot
				FALSE,                                // shared?
				1,                                    // channel offset
				&temp_neighbor,                       // neighbor
				1,									  // track ID
				1,									  // bierbitindex
				TRUE
		);
		schedule_addActiveSlot(
				19,                   // slot offset
				CELLTYPE_TX,                  		  // type of slot
				FALSE,                                // shared?
				3,                                    // channel offset
				&temp_neighbor,                       // neighbor
				1,									  // track ID
				3,									  // bierbitindex
				TRUE
		);
			schedule_addActiveSlot(
					24,                   // slot offset
					CELLTYPE_RX,                  		  // type of slot
					FALSE,                                // shared?
					1,                                    // channel offset
					&temp_neighbor,                       // neighbor
					4,									  // track ID
					1,									  // bierbitindex
					TRUE
			);
			schedule_addActiveSlot(
					26,                   // slot offset
					CELLTYPE_TX,                  		  // type of slot
					FALSE,                                // shared?
					3,                                    // channel offset
					&temp_neighbor,                       // neighbor
					4,									  // track ID
					3,									  // bierbitindex
					TRUE
			);
			schedule_addActiveSlot(
					34,                   // slot offset
					CELLTYPE_RX,                  		  // type of slot
					FALSE,                                // shared?
					4,                                    // channel offset
					&temp_neighbor,                       // neighbor
					5,									  // track ID
					3,									  // bierbitindex
					TRUE
			);
			schedule_addActiveSlot(
					36,                   // slot offset
					CELLTYPE_TX,                  		  // type of slot
					FALSE,                                // shared?
					6,                                    // channel offset
					&temp_neighbor,                       // neighbor
					5,									  // track ID
					5,									  // bierbitindex
					TRUE
			);
			schedule_addActiveSlot(
					37,                   // slot offset
					CELLTYPE_RX,                  		  // type of slot
					FALSE,                                // shared?
					7,                                    // channel offset
					&temp_neighbor,                       // neighbor
					5,									  // track ID
					5,									  // bierbitindex
					TRUE
			);
			schedule_addActiveSlot(
					38,                   // slot offset
					CELLTYPE_TX,                  		  // type of slot
					FALSE,                                // shared?
					8,                                    // channel offset
					&temp_neighbor,                       // neighbor
					5,									  // track ID
					6,									  // bierbitindex
					TRUE
			);
			schedule_addActiveSlot(
					48,                   // slot offset
					CELLTYPE_RX,                  		  // type of slot
					FALSE,                                // shared?
					3,                                    // channel offset
					&temp_neighbor,                       // neighbor
					6,									  // track ID
					2,									  // bierbitindex
					TRUE
			);
			schedule_addActiveSlot(
					49,                   // slot offset
					CELLTYPE_TX,                  		  // type of slot
					FALSE,                                // shared?
					5,                                    // channel offset
					&temp_neighbor,                       // neighbor
					6,									  // track ID
					4,									  // bierbitindex
					TRUE
			);
			schedule_addActiveSlot(
					50,                   // slot offset
					CELLTYPE_RX,                  		  // type of slot
					FALSE,                                // shared?
					6,                                    // channel offset
					&temp_neighbor,                       // neighbor
					6,									  // track ID
					4,									  // bierbitindex
					TRUE
			);
			schedule_addActiveSlot(
					51,                   // slot offset
					CELLTYPE_TX,                  		  // type of slot
					FALSE,                                // shared?
					7,                                    // channel offset
					&temp_neighbor,                       // neighbor
					6,									  // track ID
					5,									  // bierbitindex
					TRUE
			);
		break;
	case 0xc7 :
		schedule_addActiveSlot(
				18,                   // slot offset
				CELLTYPE_RX,                  		  // type of slot
				FALSE,                                // shared?
				2,                                    // channel offset
				&temp_neighbor,                       // neighbor
				1,									  // track ID
				2,									  // bierbitindex
				TRUE
		);
			schedule_addActiveSlot(
					19,                   // slot offset
					CELLTYPE_TX,                  		  // type of slot
					FALSE,                                // shared?
					4,                                    // channel offset
					&temp_neighbor,                       // neighbor
					1,									  // track ID
					4,									  // bierbitindex
					TRUE
			);
			schedule_addActiveSlot(
					25,                   // slot offset
					CELLTYPE_RX,                  		  // type of slot
					FALSE,                                // shared?
					2,                                    // channel offset
					&temp_neighbor,                       // neighbor
					4,									  // track ID
					2,									  // bierbitindex
					TRUE
			);
			schedule_addActiveSlot(
					27,                   // slot offset
					CELLTYPE_TX,                  		  // type of slot
					FALSE,                                // shared?
					4,                                    // channel offset
					&temp_neighbor,                       // neighbor
					4,									  // track ID
					4,									  // bierbitindex
					TRUE
			);
			schedule_addActiveSlot(
					35,                   // slot offset
					CELLTYPE_RX,                  		  // type of slot
					FALSE,                                // shared?
					5,                                    // channel offset
					&temp_neighbor,                       // neighbor
					5,									  // track ID
					4,									  // bierbitindex
					TRUE
			);
			schedule_addActiveSlot(
					36,                   // slot offset
					CELLTYPE_RX,                  		  // type of slot
					FALSE,                                // shared?
					6,                                    // channel offset
					&temp_neighbor,                       // neighbor
					5,									  // track ID
					5,									  // bierbitindex
					TRUE
			);
			schedule_addActiveSlot(
					37,                   // slot offset
					CELLTYPE_TX,                  		  // type of slot
					FALSE,                                // shared?
					7,                                    // channel offset
					&temp_neighbor,                       // neighbor
					5,									  // track ID
					5,									  // bierbitindex
					TRUE
			);
			schedule_addActiveSlot(
					39,                   // slot offset
					CELLTYPE_TX,                  		  // type of slot
					FALSE,                                // shared?
					9,                                    // channel offset
					&temp_neighbor,                       // neighbor
					5,									  // track ID
					7,									  // bierbitindex
					TRUE
			);
			schedule_addActiveSlot(
					48,                   // slot offset
					CELLTYPE_RX,                  		  // type of slot
					FALSE,                                // shared?
					4,                                    // channel offset
					&temp_neighbor,                       // neighbor
					6,									  // track ID
					3,									  // bierbitindex
					TRUE
			);
			schedule_addActiveSlot(
					49,                   // slot offset
					CELLTYPE_RX,                  		  // type of slot
					FALSE,                                // shared?
					5,                                    // channel offset
					&temp_neighbor,                       // neighbor
					6,									  // track ID
					4,									  // bierbitindex
					TRUE
			);
			schedule_addActiveSlot(
					50,                   // slot offset
					CELLTYPE_TX,                  		  // type of slot
					FALSE,                                // shared?
					6,                                    // channel offset
					&temp_neighbor,                       // neighbor
					6,									  // track ID
					4,									  // bierbitindex
					TRUE
			);
			schedule_addActiveSlot(
					51,                   // slot offset
					CELLTYPE_TX,                  		  // type of slot
					FALSE,                                // shared?
					8,                                    // channel offset
					&temp_neighbor,                       // neighbor
					6,									  // track ID
					6,									  // bierbitindex
					TRUE
			);
		break;
	case 0xf6 :
		schedule_addActiveSlot(
				19,                   // slot offset
				CELLTYPE_RX,                  		  // type of slot
				FALSE,                                // shared?
				3,                                    // channel offset
				&temp_neighbor,                       // neighbor
				1,									  // track ID
				3,									  // bierbitindex
				TRUE
		);
			schedule_addActiveSlot(
					20,                   // slot offset
					CELLTYPE_TX,                  		  // type of slot
					FALSE,                                // shared?
					5,                                    // channel offset
					&temp_neighbor,                       // neighbor
					1,									  // track ID
					5,									  // bierbitindex
					TRUE
			);
			schedule_addActiveSlot(
					26,                   // slot offset
					CELLTYPE_RX,                  		  // type of slot
					FALSE,                                // shared?
					3,                                    // channel offset
					&temp_neighbor,                       // neighbor
					4,									  // track ID
					3,									  // bierbitindex
					TRUE
			);
			schedule_addActiveSlot(
					28,                   // slot offset
					CELLTYPE_TX,                  		  // type of slot
					FALSE,                                // shared?
					5,                                    // channel offset
					&temp_neighbor,                       // neighbor
					4,									  // track ID
					5,									  // bierbitindex
					TRUE
			);
			schedule_addActiveSlot(
					38,                   // slot offset
					CELLTYPE_RX,                  		  // type of slot
					FALSE,                                // shared?
					8,                                    // channel offset
					&temp_neighbor,                       // neighbor
					5,									  // track ID
					6,									  // bierbitindex
					TRUE
			);
			schedule_addActiveSlot(
					40,                   // slot offset
					CELLTYPE_TX,                  		  // type of slot
					FALSE,                                // shared?
					10,                                    // channel offset
					&temp_neighbor,                       // neighbor
					5,									  // track ID
					8,									  // bierbitindex
					TRUE
			);
			schedule_addActiveSlot(
					41,                   // slot offset
					CELLTYPE_RX,                  		  // type of slot
					FALSE,                                // shared?
					11,                                    // channel offset
					&temp_neighbor,                       // neighbor
					5,									  // track ID
					8,									  // bierbitindex
					TRUE
			);
			schedule_addActiveSlot(
					42,                   // slot offset
					CELLTYPE_TX,                  		  // type of slot
					FALSE,                                // shared?
					12,                                    // channel offset
					&temp_neighbor,                       // neighbor
					5,									  // track ID
					9,									  // bierbitindex
					TRUE
			);
			schedule_addActiveSlot(
					51,                   // slot offset
					CELLTYPE_RX,                  		  // type of slot
					FALSE,                                // shared?
					7,                                    // channel offset
					&temp_neighbor,                       // neighbor
					6,									  // track ID
					5,									  // bierbitindex
					TRUE
			);
			schedule_addActiveSlot(
					52,                   // slot offset
					CELLTYPE_TX,                  		  // type of slot
					FALSE,                                // shared?
					9,                                    // channel offset
					&temp_neighbor,                       // neighbor
					6,									  // track ID
					7,									  // bierbitindex
					TRUE
			);
			schedule_addActiveSlot(
					53,                   // slot offset
					CELLTYPE_RX,                  		  // type of slot
					FALSE,                                // shared?
					10,                                    // channel offset
					&temp_neighbor,                       // neighbor
					6,									  // track ID
					7,									  // bierbitindex
					TRUE
			);
			schedule_addActiveSlot(
					54,                   // slot offset
					CELLTYPE_TX,                  		  // type of slot
					FALSE,                                // shared?
					11,                                    // channel offset
					&temp_neighbor,                       // neighbor
					6,									  // track ID
					8,									  // bierbitindex
					TRUE
			);
			break;
	case 0xec :
		schedule_addActiveSlot(
				19,                   // slot offset
				CELLTYPE_RX,                  		  // type of slot
				FALSE,                                // shared?
				4,                                    // channel offset
				&temp_neighbor,                       // neighbor
				1,									  // track ID
				4,									  // bierbitindex
				TRUE
		);
			schedule_addActiveSlot(
					21,                   // slot offset
					CELLTYPE_TX,                  		  // type of slot
					FALSE,                                // shared?
					6,                                    // channel offset
					&temp_neighbor,                       // neighbor
					1,									  // track ID
					6,									  // bierbitindex
					TRUE
			);
			schedule_addActiveSlot(
					27,                   // slot offset
					CELLTYPE_RX,                  		  // type of slot
					FALSE,                                // shared?
					4,                                    // channel offset
					&temp_neighbor,                       // neighbor
					4,									  // track ID
					4,									  // bierbitindex
					TRUE
			);
			schedule_addActiveSlot(
					29,                   // slot offset
					CELLTYPE_TX,                  		  // type of slot
					FALSE,                                // shared?
					6,                                    // channel offset
					&temp_neighbor,                       // neighbor
					4,									  // track ID
					6,									  // bierbitindex
					TRUE
			);
			schedule_addActiveSlot(
					39,                   // slot offset
					CELLTYPE_RX,                  		  // type of slot
					FALSE,                                // shared?
					9,                                    // channel offset
					&temp_neighbor,                       // neighbor
					5,									  // track ID
					7,									  // bierbitindex
					TRUE
			);
			schedule_addActiveSlot(
					40,                   // slot offset
					CELLTYPE_RX,                  		  // type of slot
					FALSE,                                // shared?
					10,                                    // channel offset
					&temp_neighbor,                       // neighbor
					5,									  // track ID
					8,									  // bierbitindex
					TRUE
			);
			schedule_addActiveSlot(
					41,                   // slot offset
					CELLTYPE_TX,                  		  // type of slot
					FALSE,                                // shared?
					11,                                    // channel offset
					&temp_neighbor,                       // neighbor
					5,									  // track ID
					8,									  // bierbitindex
					TRUE
			);
			schedule_addActiveSlot(
					43,                   // slot offset
					CELLTYPE_TX,                  		  // type of slot
					FALSE,                                // shared?
					13,                                    // channel offset
					&temp_neighbor,                       // neighbor
					5,									  // track ID
					10,									  // bierbitindex
					TRUE
			);
			schedule_addActiveSlot(
					51,                   // slot offset
					CELLTYPE_RX,                  		  // type of slot
					FALSE,                                // shared?
					8,                                    // channel offset
					&temp_neighbor,                       // neighbor
					6,									  // track ID
					6,									  // bierbitindex
					TRUE
			);
			schedule_addActiveSlot(
					52,                   // slot offset
					CELLTYPE_RX,                  		  // type of slot
					FALSE,                                // shared?
					9,                                    // channel offset
					&temp_neighbor,                       // neighbor
					6,									  // track ID
					7,									  // bierbitindex
					TRUE
			);
			schedule_addActiveSlot(
					53,                   // slot offset
					CELLTYPE_TX,                  		  // type of slot
					FALSE,                                // shared?
					10,                                    // channel offset
					&temp_neighbor,                       // neighbor
					6,									  // track ID
					7,									  // bierbitindex
					TRUE
			);
			schedule_addActiveSlot(
					55,                   // slot offset
					CELLTYPE_TX,                  		  // type of slot
					FALSE,                                // shared?
					12,                                    // channel offset
					&temp_neighbor,                       // neighbor
					6,									  // track ID
					9,									  // bierbitindex
					TRUE
			);
		break;
	case 0xc3 :
		schedule_addActiveSlot(
				20,                   // slot offset
				CELLTYPE_RX,                  		  // type of slot
				FALSE,                                // shared?
				5,                                    // channel offset
				&temp_neighbor,                       // neighbor
				1,									  // track ID
				5,									  // bierbitindex
				TRUE
		);
			schedule_addActiveSlot(
					21,                   // slot offset
					CELLTYPE_RX,                  		  // type of slot
					FALSE,                                // shared?
					6,                                    // channel offset
					&temp_neighbor,                       // neighbor
					1,									  // track ID
					6,									  // bierbitindex
					TRUE
			);
			schedule_addActiveSlot(
					28,                   // slot offset
					CELLTYPE_RX,                  		  // type of slot
					FALSE,                                // shared?
					5,                                    // channel offset
					&temp_neighbor,                       // neighbor
					4,									  // track ID
					5,									  // bierbitindex
					TRUE
			);
			schedule_addActiveSlot(
					29,                   // slot offset
					CELLTYPE_RX,                  		  // type of slot
					FALSE,                                // shared?
					6,                                    // channel offset
					&temp_neighbor,                       // neighbor
					4,									  // track ID
					6,									  // bierbitindex
					TRUE
			);
			schedule_addActiveSlot(
					42,                   // slot offset
					CELLTYPE_RX,                  		  // type of slot
					FALSE,                                // shared?
					12,                                    // channel offset
					&temp_neighbor,                       // neighbor
					5,									  // track ID
					9,									  // bierbitindex
					TRUE
			);
			schedule_addActiveSlot(
					43,                   // slot offset
					CELLTYPE_RX,                  		  // type of slot
					FALSE,                                // shared?
					13,                                    // channel offset
					&temp_neighbor,                       // neighbor
					5,									  // track ID
					10,									  // bierbitindex
					TRUE
			);
			schedule_addActiveSlot(
					54,                   // slot offset
					CELLTYPE_RX,                  		  // type of slot
					FALSE,                                // shared?
					11,                                    // channel offset
					&temp_neighbor,                       // neighbor
					6,									  // track ID
					8,									  // bierbitindex
					TRUE
			);
			schedule_addActiveSlot(
					55,                   // slot offset
					CELLTYPE_RX,                  		  // type of slot
					FALSE,                                // shared?
					12,                                    // channel offset
					&temp_neighbor,                       // neighbor
					6,									  // track ID
					9,									  // bierbitindex
					TRUE
			);
		break;
	default :
		break;
	}

	// track 2 and 3 slots :
	for (running_slotOffset=57;running_slotOffset<69;running_slotOffset++) {
		schedule_addActiveSlot(
				running_slotOffset,                    // slot offset
				CELLTYPE_TXRX,                     // type of slot
				FALSE,                                 // shared?
				(running_slotOffset-10)%16,                                     // channel offset
				&temp_neighbor,                        // neighbor
				2,										// trackID
				0,										// bundleID
				FALSE                                  // bier
		);
	}
	for (running_slotOffset=70;running_slotOffset<82;running_slotOffset++) {
		schedule_addActiveSlot(
				running_slotOffset,                    // slot offset
				CELLTYPE_TXRX,                     // type of slot
				FALSE,                                 // shared?
				(running_slotOffset-10)%16,                                     // channel offset
				&temp_neighbor,                        // neighbor
				3,										// trackID
				0,										// bundleID
				FALSE                                  // bier
		);
	}

	// shared sync slots
	schedule_addActiveSlot(
			16,                 // slot offset
			CELLTYPE_TXRX,                      // type of slot
			TRUE,                               // shared?
			SCHEDULE_MINIMAL_6TISCH_CHANNELOFFSET,    // channel offset
			&temp_neighbor,                      // neighbor
			0,									  // trackID
			0,									  // bundleID
			FALSE                                // bier
	);
	schedule_addActiveSlot(
			22,                 // slot offset
			CELLTYPE_TXRX,                      // type of slot
			TRUE,                               // shared?
			SCHEDULE_MINIMAL_6TISCH_CHANNELOFFSET,    // channel offset
			&temp_neighbor,                      // neighbor
			0,									  // trackID
			0,									  // bundleID
			FALSE                                // bier
	);
	schedule_addActiveSlot(
			44,                 // slot offset
			CELLTYPE_TXRX,                      // type of slot
			TRUE,                               // shared?
			SCHEDULE_MINIMAL_6TISCH_CHANNELOFFSET,    // channel offset
			&temp_neighbor,                      // neighbor
			0,									  // trackID
			0,									  // bundleID
			FALSE                                // bier
	);
	schedule_addActiveSlot(
			56,                 // slot offset
			CELLTYPE_TXRX,                      // type of slot
			TRUE,                               // shared?
			SCHEDULE_MINIMAL_6TISCH_CHANNELOFFSET,    // channel offset
			&temp_neighbor,                      // neighbor
			0,									  // trackID
			0,									  // bundleID
			FALSE                                // bier
	);
	schedule_addActiveSlot(
			69,                 // slot offset
			CELLTYPE_TXRX,                      // type of slot
			TRUE,                               // shared?
			SCHEDULE_MINIMAL_6TISCH_CHANNELOFFSET,    // channel offset
			&temp_neighbor,                      // neighbor
			0,									  // trackID
			0,									  // bundleID
			FALSE                                // bier
	);
}

/**
\brief Starting the DAGroot schedule propagation.
*/
void schedule_startDAGroot() {
   slotOffset_t    start_slotOffset;
   slotOffset_t    running_slotOffset;
   open_addr_t     temp_neighbor;
   
   start_slotOffset = SCHEDULE_MINIMAL_6TISCH_SLOTOFFSET;
   // set frame length, handle and number (default 1 by now)
   if (schedule_vars.frameLength == 0) {
       // slotframe length is not set, set it to default length
       schedule_setFrameLength(SLOTFRAME_LENGTH);
   } else {
       // slotframe elgnth is set, nothing to do here
   }
   schedule_setFrameHandle(SCHEDULE_MINIMAL_6TISCH_DEFAULT_SLOTFRAME_HANDLE);
   schedule_setFrameNumber(SCHEDULE_MINIMAL_6TISCH_DEFAULT_SLOTFRAME_NUMBER);

   // shared TXRX anycast slot(s)
   memset(&temp_neighbor,0,sizeof(temp_neighbor));
   temp_neighbor.type             = ADDR_ANYCAST;
   for (running_slotOffset=start_slotOffset;running_slotOffset<start_slotOffset+SCHEDULE_MINIMAL_6TISCH_ACTIVE_CELLS;running_slotOffset++) {
      schedule_addActiveSlot(
         running_slotOffset,                 // slot offset
         CELLTYPE_TXRX,                      // type of slot
         TRUE,                               // shared?
         SCHEDULE_MINIMAL_6TISCH_CHANNELOFFSET,    // channel offset
         &temp_neighbor,                      // neighbor
		 0,									  // trackID
		 0,									  // bundleID
		 FALSE                                // bier
      );
   }
}

/**
\brief Trigger this module to print status information, over serial.

debugPrint_* functions are used by the openserial module to continuously print
status information about several modules in the OpenWSN stack.

\returns TRUE if this function printed something, FALSE otherwise.
*/
bool debugPrint_schedule() {
   debugScheduleEntry_t temp;
   
   // increment the row just printed
   schedule_vars.debugPrintRow         = (schedule_vars.debugPrintRow+1)%schedule_vars.maxActiveSlots;
   
   // gather status data
   temp.row                            = schedule_vars.debugPrintRow;
   temp.slotOffset                     = \
      schedule_vars.scheduleBuf[schedule_vars.debugPrintRow].slotOffset;
   temp.type                           = \
      schedule_vars.scheduleBuf[schedule_vars.debugPrintRow].type;
   temp.shared                         = \
      schedule_vars.scheduleBuf[schedule_vars.debugPrintRow].shared;
   temp.channelOffset                  = \
      schedule_vars.scheduleBuf[schedule_vars.debugPrintRow].channelOffset;
   memcpy(
      &temp.neighbor,
      &schedule_vars.scheduleBuf[schedule_vars.debugPrintRow].neighbor,
      sizeof(open_addr_t)
   );
   temp.numRx                          = \
      schedule_vars.scheduleBuf[schedule_vars.debugPrintRow].numRx;
   temp.numTx                          = \
      schedule_vars.scheduleBuf[schedule_vars.debugPrintRow].numTx;
   temp.numTxACK                       = \
      schedule_vars.scheduleBuf[schedule_vars.debugPrintRow].numTxACK;
   memcpy(
      &temp.lastUsedAsn,
      &schedule_vars.scheduleBuf[schedule_vars.debugPrintRow].lastUsedAsn,
      sizeof(asn_t)
   );
   temp.trackID                       = \
      schedule_vars.scheduleBuf[schedule_vars.debugPrintRow].trackID;
   temp.bundleID                       = \
      schedule_vars.scheduleBuf[schedule_vars.debugPrintRow].bundleID;
   
   // send status data over serial port
   openserial_printStatus(
      STATUS_SCHEDULE,
      (uint8_t*)&temp,
      sizeof(debugScheduleEntry_t)
   );
   
   return TRUE;
}

/**
\brief Trigger this module to print status information, over serial.

debugPrint_* functions are used by the openserial module to continuously print
status information about several modules in the OpenWSN stack.

\returns TRUE if this function printed something, FALSE otherwise.
*/
bool debugPrint_backoff() {
   uint8_t temp[2];
   
   // gather status data
   temp[0] = schedule_vars.backoffExponent;
   temp[1] = schedule_vars.backoff;
   
   // send status data over serial port
   openserial_printStatus(
      STATUS_BACKOFF,
      (uint8_t*)&temp,
      sizeof(temp)
   );
   
   return TRUE;
}

//=== from 6top (writing the schedule)

/**
\brief Set frame length.

\param newFrameLength The new frame length.
*/
void schedule_setFrameLength(frameLength_t newFrameLength) {
   
   INTERRUPT_DECLARATION();
   DISABLE_INTERRUPTS();
   schedule_vars.frameLength = newFrameLength;
   if (newFrameLength <= schedule_vars.maxActiveSlots) {
      schedule_vars.maxActiveSlots = newFrameLength;
   }
   openserial_printInfo(COMPONENT_SCHEDULE,
                        ERR_SCHEDULE_LENGTHCHANGED,
                        (errorparameter_t) schedule_vars.frameLength,
                        (errorparameter_t) schedule_vars.maxActiveSlots);
   ENABLE_INTERRUPTS();
}

/**
\brief Set frame handle.

\param frameHandle The new frame handle.
*/
void schedule_setFrameHandle(uint8_t frameHandle) {
   
   INTERRUPT_DECLARATION();
   DISABLE_INTERRUPTS();
   
   schedule_vars.frameHandle = frameHandle;
   
   ENABLE_INTERRUPTS();
}

/**
\brief Set frame number.

\param frameNumber The new frame number.
*/
void schedule_setFrameNumber(uint8_t frameNumber) {
   
   INTERRUPT_DECLARATION();
   DISABLE_INTERRUPTS();
   
   schedule_vars.frameNumber = frameNumber;
   
   ENABLE_INTERRUPTS();
}

/**
\brief Get the information of a specific slot.

\param slotOffset
\param neighbor
\param info
*/
void  schedule_getSlotInfo(
   slotOffset_t         slotOffset,
   open_addr_t*         neighbor,
   slotinfo_element_t*  info
){
   
   scheduleEntry_t* slotContainer;
  
   // find an empty schedule entry container
   slotContainer = &schedule_vars.scheduleBuf[0];
   while (slotContainer<=&schedule_vars.scheduleBuf[schedule_vars.maxActiveSlots-1]) {
       //check that this entry for that neighbour and timeslot is not already scheduled.
       if (packetfunctions_sameAddress(neighbor,&(slotContainer->neighbor))&& (slotContainer->slotOffset==slotOffset)){
               //it exists so this is an update.
               info->link_type                 = slotContainer->type;
               info->shared                    = slotContainer->shared;
               info->channelOffset             = slotContainer->channelOffset;
               return; //as this is an update. No need to re-insert as it is in the same position on the list.
        }
        slotContainer++;
   }
   //return cell type off.
   info->link_type                 = CELLTYPE_OFF;
   info->shared                    = FALSE;
   info->channelOffset             = 0;//set to zero if not set.                          
}

/**
\brief Get the maximum number of active slots.

\param[out] maximum number of active slots
*/
uint16_t  schedule_getMaxActiveSlots() {
   return schedule_vars.maxActiveSlots;
}

/**
\brief Get the information of a specific BIER slot.

\param slotOffset
\param info
*/
void  schedule_controllerGetSlotInfo(
        slotOffset_t         slotOffset,
        slotinfo_element_t*  info
){

   scheduleEntry_t* slotContainer;

   // find an empty schedule entry container
   slotContainer = &schedule_vars.scheduleBuf[0];
   while (slotContainer<=&schedule_vars.scheduleBuf[schedule_vars.maxActiveSlots-1]) {
      //check that this entry for that neighbour and timeslot is not already scheduled.
      if ((slotContainer -> trackID) && (slotContainer->slotOffset==slotOffset)){
         //it exists so this is an update.
         info->link_type                 = slotContainer->type;
         info->shared                    = slotContainer->shared;
         info->channelOffset             = slotContainer->channelOffset;
         info->trackID                   = slotContainer->trackID;
         info->bundleID                  = slotContainer->bundleID;
         return; //as this is an update. No need to re-insert as it is in the same position on the list.
      }
      slotContainer++;
   }
   //return cell type off.
   info->link_type                 = CELLTYPE_OFF;
   info->shared                    = FALSE;
   info->channelOffset             = 0;//set to zero if not set.
   info->trackID                   = 0;
   info->bundleID                  = 0;
}

/**
\brief Add a new active slot into the schedule.

\param slotOffset       The slotoffset of the new slot
\param type             The type of the cell
\param shared           Whether this cell is shared (TRUE) or not (FALSE).
\param channelOffset    The channelOffset of the new slot
\param neighbor         The neighbor associated with this cell (all 0's if
   none)
*/
owerror_t schedule_addActiveSlot(
      slotOffset_t    slotOffset,
      cellType_t      type,
      bool            shared,
      channelOffset_t channelOffset,
      open_addr_t*    neighbor,
	  uint8_t         trackID,
	  uint16_t		  bundleID,
	  bool            bier
   ) {

   scheduleEntry_t* slotContainer;
   scheduleEntry_t* previousSlotWalker;
   scheduleEntry_t* nextSlotWalker;
   
   INTERRUPT_DECLARATION();
   DISABLE_INTERRUPTS();
   
   // find an empty schedule entry container
   slotContainer = &schedule_vars.scheduleBuf[0];
   while (
         slotContainer->type!=CELLTYPE_OFF &&
         slotContainer<=&schedule_vars.scheduleBuf[schedule_vars.maxActiveSlots-1]
      ) {
      slotContainer++;
   }
   
   // abort it schedule overflow
   if (slotContainer>&schedule_vars.scheduleBuf[schedule_vars.maxActiveSlots-1]) {
      ENABLE_INTERRUPTS();
      openserial_printCritical(
         COMPONENT_SCHEDULE,ERR_SCHEDULE_OVERFLOWN,
         (errorparameter_t)0,
         (errorparameter_t)0
      );
      return E_FAIL;
   }
   
   // fill that schedule entry with parameters passed
   slotContainer->slotOffset                = slotOffset;
   slotContainer->type                      = type;
   slotContainer->shared                    = shared;
   slotContainer->channelOffset             = channelOffset;
   slotContainer->trackID					= trackID;
   slotContainer->bundleID					= bundleID;
   slotContainer->bierDoNotSend				= FALSE;
   slotContainer->bier						= bier;
   memcpy(&slotContainer->neighbor,neighbor,sizeof(open_addr_t));
   
   // insert in circular list
   if (schedule_vars.currentScheduleEntry==NULL) {
      // this is the first active slot added
      
      // the next slot of this slot is this slot
      slotContainer->next                   = slotContainer;
      
      // current slot points to this slot
      schedule_vars.currentScheduleEntry    = slotContainer;
   } else  {
      // this is NOT the first active slot added
      
      // find position in schedule
      previousSlotWalker                    = schedule_vars.currentScheduleEntry;
      while (1) {
         nextSlotWalker                     = previousSlotWalker->next;
         if (
               (
                     (previousSlotWalker->slotOffset <  slotContainer->slotOffset) &&
                     (slotContainer->slotOffset <  nextSlotWalker->slotOffset)
               )
               ||
               (
                     (previousSlotWalker->slotOffset <  slotContainer->slotOffset) &&
                     (nextSlotWalker->slotOffset <= previousSlotWalker->slotOffset)
               )
               ||
               (
                     (slotContainer->slotOffset <  nextSlotWalker->slotOffset) &&
                     (nextSlotWalker->slotOffset <= previousSlotWalker->slotOffset)
               )
         ) {
            break;
         }
         if (previousSlotWalker->slotOffset == slotContainer->slotOffset) {
            // slot is already in schedule
            openserial_printError(
               COMPONENT_SCHEDULE,
               ERR_SCHEDULE_ADDDUPLICATESLOT,
               (errorparameter_t)slotContainer->slotOffset,
               (errorparameter_t)0
            );
            ENABLE_INTERRUPTS();
            return E_FAIL;
         }
         previousSlotWalker                 = nextSlotWalker;
      }
      // insert between previousSlotWalker and nextSlotWalker
      previousSlotWalker->next              = slotContainer;
      slotContainer->next                   = nextSlotWalker;
   }
   
   ENABLE_INTERRUPTS();
   return E_SUCCESS;
}

/**
\brief Remove an active slot from the schedule.

\param slotOffset       The slotoffset of the slot to remove.
\param neighbor         The neighbor associated with this cell (all 0's if
   none)
*/
owerror_t schedule_removeActiveSlot(slotOffset_t slotOffset, open_addr_t* neighbor) {
   scheduleEntry_t* slotContainer;
   scheduleEntry_t* previousSlotWalker;
   
   INTERRUPT_DECLARATION();
   DISABLE_INTERRUPTS();
   
   // find the schedule entry
   slotContainer = &schedule_vars.scheduleBuf[0];
   while (slotContainer<=&schedule_vars.scheduleBuf[schedule_vars.maxActiveSlots-1]) {
      if (
            slotContainer->slotOffset==slotOffset
            &&
            packetfunctions_sameAddress(neighbor,&(slotContainer->neighbor))
            ){
         break;
      }
      slotContainer++;
   }
   
   // abort it could not find
   if (slotContainer>&schedule_vars.scheduleBuf[schedule_vars.maxActiveSlots-1]) {
      ENABLE_INTERRUPTS();
      openserial_printCritical(
         COMPONENT_SCHEDULE,ERR_FREEING_ERROR,
         (errorparameter_t)0,
         (errorparameter_t)0
      );
      return E_FAIL;
   }
   
   // remove from linked list
   if (slotContainer->next==slotContainer) {
      // this is the last active slot
      
      // the next slot of this slot is NULL
      slotContainer->next                   = NULL;
      
      // current slot points to this slot
      schedule_vars.currentScheduleEntry    = NULL;
   } else  {
      // this is NOT the last active slot
      
      // find the previous in the schedule
      previousSlotWalker                    = schedule_vars.currentScheduleEntry;
      
      while (1) {
         if (previousSlotWalker->next==slotContainer){
            break;
         }
         previousSlotWalker                 = previousSlotWalker->next;
      }
      
      // remove this element from the linked list, i.e. have the previous slot
      // "jump" to slotContainer's next
      previousSlotWalker->next              = slotContainer->next;
      
      // update current slot if points to slot I just removed
      if (schedule_vars.currentScheduleEntry==slotContainer) {
         schedule_vars.currentScheduleEntry = slotContainer->next;
      }
   }
   
   // reset removed schedule entry
   schedule_resetEntry(slotContainer);
   
   ENABLE_INTERRUPTS();
   
   return E_SUCCESS;
}

owerror_t schedule_controllerRemoveActiveSlot(slotOffset_t slotOffset) {
   scheduleEntry_t* slotContainer;
   scheduleEntry_t* previousSlotWalker;

   INTERRUPT_DECLARATION();
   DISABLE_INTERRUPTS();

   // find the schedule entry
   slotContainer = &schedule_vars.scheduleBuf[0];
   while (slotContainer<=&schedule_vars.scheduleBuf[schedule_vars.maxActiveSlots-1]) {
      if (slotContainer->slotOffset==slotOffset){
         break;
      }
      slotContainer++;
   }

   // abort it could not find
   if (slotContainer>&schedule_vars.scheduleBuf[schedule_vars.maxActiveSlots-1]) {
      ENABLE_INTERRUPTS();
      openserial_printCritical(
              COMPONENT_SCHEDULE,ERR_FREEING_ERROR,
              (errorparameter_t)0,
              (errorparameter_t)0
      );
      return E_FAIL;
   }

   // remove from linked list
   if (slotContainer->next==slotContainer) {
      // this is the last active slot

      // the next slot of this slot is NULL
      slotContainer->next                   = NULL;

      // current slot points to this slot
      schedule_vars.currentScheduleEntry    = NULL;
   } else  {
      // this is NOT the last active slot

      // find the previous in the schedule
      previousSlotWalker                    = schedule_vars.currentScheduleEntry;

      while (1) {
         if (previousSlotWalker->next==slotContainer){
            break;
         }
         previousSlotWalker                 = previousSlotWalker->next;
      }

      // remove this element from the linked list, i.e. have the previous slot
      // "jump" to slotContainer's next
      previousSlotWalker->next              = slotContainer->next;

      // update current slot if points to slot I just removed
      if (schedule_vars.currentScheduleEntry==slotContainer) {
         schedule_vars.currentScheduleEntry = slotContainer->next;
      }
   }

   // reset removed schedule entry
   schedule_resetEntry(slotContainer);

   ENABLE_INTERRUPTS();

   return E_SUCCESS;
}

bool schedule_isSlotOffsetAvailable(uint16_t slotOffset){
   
   scheduleEntry_t* scheduleWalker;
   
   INTERRUPT_DECLARATION();
   DISABLE_INTERRUPTS();
   
   scheduleWalker = schedule_vars.currentScheduleEntry;
   do {
      if(slotOffset == scheduleWalker->slotOffset){
          ENABLE_INTERRUPTS();
          return FALSE;
      }
      scheduleWalker = scheduleWalker->next;
   }while(scheduleWalker!=schedule_vars.currentScheduleEntry);
   
   ENABLE_INTERRUPTS();
   
   return TRUE;
}

scheduleEntry_t* schedule_statistic_poorLinkQuality(){
   scheduleEntry_t* scheduleWalker;
   
   INTERRUPT_DECLARATION();
   DISABLE_INTERRUPTS();
   
   scheduleWalker = schedule_vars.currentScheduleEntry;
   do {
      if(
         scheduleWalker->numTx > MIN_NUMTX_FOR_PDR                     &&\
         PDR_THRESHOLD > 100*scheduleWalker->numTxACK/scheduleWalker->numTx &&\
		 !scheduleWalker->bier	// Do not care about BIER slots here
      ){
         break;
      }
      scheduleWalker = scheduleWalker->next;
   }while(scheduleWalker!=schedule_vars.currentScheduleEntry);
   
   if (scheduleWalker == schedule_vars.currentScheduleEntry){
       ENABLE_INTERRUPTS();
       return NULL;
   } else {
       ENABLE_INTERRUPTS();
       return scheduleWalker;
   }
}

uint16_t  schedule_getCellsCounts(uint8_t frameID,cellType_t type, open_addr_t* neighbor){
    uint16_t         count = 0;
    scheduleEntry_t* scheduleWalker;
   
    INTERRUPT_DECLARATION();
    DISABLE_INTERRUPTS();
    
    if (frameID != SCHEDULE_MINIMAL_6TISCH_DEFAULT_SLOTFRAME_HANDLE){
        ENABLE_INTERRUPTS();
        return 0;
    }
   
    scheduleWalker = schedule_vars.currentScheduleEntry;
    do {
       if(
          packetfunctions_sameAddress(&(scheduleWalker->neighbor),neighbor) &&
          type == scheduleWalker->type &&
		  !scheduleWalker->bier
       ){
           count++;
       }
       scheduleWalker = scheduleWalker->next;
    }while(scheduleWalker!=schedule_vars.currentScheduleEntry);
   
    ENABLE_INTERRUPTS();
    return count;
}

void schedule_sixtopRemoveAllCells(
    uint8_t        slotframeID,
    open_addr_t*   previousHop
    ){
    uint8_t i;

    // remove all entries in schedule with previousHop address except BIER entries
    for(i=0;i<schedule_vars.maxActiveSlots;i++){
        if (!schedule_vars.scheduleBuf[i].bier && packetfunctions_sameAddress(&(schedule_vars.scheduleBuf[i].neighbor),previousHop)){
           schedule_removeActiveSlot(
              schedule_vars.scheduleBuf[i].slotOffset,
              previousHop
           );
        }
    }
}

//remove all bier cell
void schedule_controllerRemoveAllBierCells(uint8_t slotFrameID){
   uint8_t i;
   // remove all BIER entries
   for(i=0;i<schedule_vars.maxActiveSlots;i++){
      if (schedule_vars.scheduleBuf[i].trackID ){
         schedule_controllerRemoveActiveSlot(schedule_vars.scheduleBuf[i].slotOffset);
      }
   }
}

scheduleEntry_t* schedule_getCurrentScheduleEntry(){
    return schedule_vars.currentScheduleEntry;
}

//=== from IEEE802154E: reading the schedule and updating statistics

void schedule_syncSlotOffset(slotOffset_t targetSlotOffset) {
   
   INTERRUPT_DECLARATION();
   DISABLE_INTERRUPTS();
   
   while (schedule_vars.currentScheduleEntry->slotOffset!=targetSlotOffset) {
      schedule_advanceSlot();
   }
   
   ENABLE_INTERRUPTS();
}

/**
\brief advance to next active slot
*/
void schedule_advanceSlot() {
   
   INTERRUPT_DECLARATION();
   DISABLE_INTERRUPTS();
   
   schedule_vars.currentScheduleEntry = schedule_vars.currentScheduleEntry->next;
   
   ENABLE_INTERRUPTS();
}

/**
\brief return slotOffset of next active slot
*/
slotOffset_t schedule_getNextActiveSlotOffset() {
   slotOffset_t res;   
   
   INTERRUPT_DECLARATION();
   DISABLE_INTERRUPTS();
   
   res = ((scheduleEntry_t*)(schedule_vars.currentScheduleEntry->next))->slotOffset;
   
   ENABLE_INTERRUPTS();
   
   return res;
}

/**
\brief Get the frame length.

\returns The frame length.
*/
frameLength_t schedule_getFrameLength() {
   frameLength_t returnVal;
   
   INTERRUPT_DECLARATION();
   DISABLE_INTERRUPTS();
   
   returnVal = schedule_vars.frameLength;
   
   ENABLE_INTERRUPTS();
   
   return returnVal;
}

/**
\brief Get the frame handle.

\returns The frame handle.
*/
uint8_t schedule_getFrameHandle() {
   uint8_t returnVal;
   
   INTERRUPT_DECLARATION();
   DISABLE_INTERRUPTS();
   
   returnVal = schedule_vars.frameHandle;
   
   ENABLE_INTERRUPTS();
   
   return returnVal;
}

/**
\brief Get the frame number.

\returns The frame number.
*/
uint8_t schedule_getFrameNumber() {
   uint8_t returnVal;
   
   INTERRUPT_DECLARATION();
   DISABLE_INTERRUPTS();
   
   returnVal = schedule_vars.frameNumber;
   
   ENABLE_INTERRUPTS();
   
   return returnVal;
}
/**
\brief Get the type of the current schedule entry.

\returns The type of the current schedule entry.
*/
cellType_t schedule_getType() {
   cellType_t returnVal;
   
   INTERRUPT_DECLARATION();
   DISABLE_INTERRUPTS();
   
   returnVal = schedule_vars.currentScheduleEntry->type;
   
   ENABLE_INTERRUPTS();
   
   return returnVal;
}

/**
\brief Get the neighbor associated wit the current schedule entry.

\returns The neighbor associated wit the current schedule entry.
*/
void schedule_getNeighbor(open_addr_t* addrToWrite) {
   
   INTERRUPT_DECLARATION();
   DISABLE_INTERRUPTS();
   
   memcpy(addrToWrite,&(schedule_vars.currentScheduleEntry->neighbor),sizeof(open_addr_t));
   
   ENABLE_INTERRUPTS();
}

/**
\brief Get the channel offset of the current schedule entry.

\returns The channel offset of the current schedule entry.
*/
channelOffset_t schedule_getChannelOffset() {
   channelOffset_t returnVal;
   
   INTERRUPT_DECLARATION();
   DISABLE_INTERRUPTS();
   
   returnVal = schedule_vars.currentScheduleEntry->channelOffset;
   
   ENABLE_INTERRUPTS();
   
   return returnVal;
}

/**
\brief Get the track ID of the current schedule entry.

\returns The track ID of the current schedule entry.
*/
uint8_t schedule_getTrackID() {
   uint8_t returnVal;

   INTERRUPT_DECLARATION();
   DISABLE_INTERRUPTS();

   returnVal = schedule_vars.currentScheduleEntry->trackID;

   ENABLE_INTERRUPTS();

   return returnVal;
}

/**
\brief Get the bundleID of the current schedule entry.

\returns The bundleID of the current schedule entry.
*/
uint16_t schedule_getBundleID() {
   uint16_t returnVal;

   INTERRUPT_DECLARATION();
   DISABLE_INTERRUPTS();

   returnVal = schedule_vars.currentScheduleEntry->bundleID;

   ENABLE_INTERRUPTS();

   return returnVal;
}

/**
\brief returns if there was a successful transmit on this bundle on this time frame.
*/
bool schedule_getBier(){
	   bool returnVal;

	   INTERRUPT_DECLARATION();
	   DISABLE_INTERRUPTS();

	   returnVal = schedule_vars.currentScheduleEntry->bier;

	   ENABLE_INTERRUPTS();

	   return returnVal;
}

/**
\brief returns if there was a successful transmit on this bundle on this time frame.
*/
bool schedule_getBierDoNotSend(){
	   bool returnVal;

	   INTERRUPT_DECLARATION();
	   DISABLE_INTERRUPTS();

	   returnVal = schedule_vars.currentScheduleEntry->bierDoNotSend;

	   ENABLE_INTERRUPTS();

	   return returnVal;
}

void schedule_setBierDoNotSend(uint8_t trackID, uint16_t bitIndex, cellType_t celltype){
	slotOffset_t running_slotOffset;

	INTERRUPT_DECLARATION();
	DISABLE_INTERRUPTS();

	for (running_slotOffset=0;running_slotOffset<schedule_vars.maxActiveSlots;running_slotOffset++) {
		if(schedule_vars.scheduleBuf[running_slotOffset].trackID==trackID &&
				schedule_vars.scheduleBuf[running_slotOffset].bundleID==bitIndex &&
				schedule_vars.scheduleBuf[running_slotOffset].type==celltype){
			schedule_vars.scheduleBuf[running_slotOffset].bierDoNotSend = 1;
		}
	}

	ENABLE_INTERRUPTS();
}

void schedule_resetBierDoNotSend(){
	slotOffset_t running_slotOffset;

	INTERRUPT_DECLARATION();
	DISABLE_INTERRUPTS();

	for (running_slotOffset=0;running_slotOffset<schedule_vars.maxActiveSlots;running_slotOffset++) {
		schedule_vars.scheduleBuf[running_slotOffset].bierDoNotSend = 0;

	}

	ENABLE_INTERRUPTS();
}

/**
\brief Check whether I can send on this slot.

This function is called at the beginning of every TX slot.
If the slot is *not* a shared slot, it always return TRUE.
If the slot is a shared slot, it decrements the backoff counter and returns 
TRUE only if it hits 0.

Note that the backoff counter is global, not per slot.

\returns TRUE if it is OK to send on this slot, FALSE otherwise.
*/
bool schedule_getOkToSend() {
   bool returnVal;
   
   INTERRUPT_DECLARATION();
   DISABLE_INTERRUPTS();
   
   if (schedule_vars.currentScheduleEntry->shared==FALSE) {
      // non-shared slot: backoff does not apply
      
      returnVal = TRUE;
   } else {
      // non-shared slot: check backoff before answering
      
      // decrement backoff
      if (schedule_vars.backoff>0) {
         schedule_vars.backoff--;
      }
      
      // only return TRUE if backoff hit 0
      if (schedule_vars.backoff==0) {
         returnVal = TRUE;
      } else {
         returnVal = FALSE;
      }
   }
   
   ENABLE_INTERRUPTS();
   
   return returnVal;
}

/**
\brief Check whether this is the last slot of the bundle.

This function is called at every BIER slot. In case I am the last slot on the bundle I will not require an ACK.

\returns TRUE if it is the last slot on this bundle, FALSE otherwise.
*/
bool schedule_isLastSlotOfBundle() {
   scheduleEntry_t* scheduleWalker;
   scheduleEntry_t* nextScheduleWalker;

   INTERRUPT_DECLARATION();
   DISABLE_INTERRUPTS();
   
   scheduleWalker = schedule_vars.currentScheduleEntry;
   nextScheduleWalker = schedule_vars.currentScheduleEntry->next;

   while(scheduleWalker->slotOffset < nextScheduleWalker->slotOffset){
	   scheduleWalker = nextScheduleWalker;
	   nextScheduleWalker = nextScheduleWalker->next;
	   if(scheduleWalker->trackID == schedule_vars.currentScheduleEntry->trackID &&
			   scheduleWalker->bundleID == schedule_vars.currentScheduleEntry->bundleID &&
			   scheduleWalker->type == schedule_vars.currentScheduleEntry->type){
		   ENABLE_INTERRUPTS();
		   return FALSE;
	   }
   }

   ENABLE_INTERRUPTS();

   return TRUE;
}


/**
\brief Reset the backoff and backoffExponent.
*/
void schedule_resetBackoff() {

   INTERRUPT_DECLARATION();
   DISABLE_INTERRUPTS();

   // reset backoffExponent
   schedule_vars.backoffExponent = MINBE-1;
   // reset backoff
   schedule_vars.backoff         = 0;
   
   ENABLE_INTERRUPTS();
}

/**
\brief Indicate the reception of a packet.
*/
void schedule_indicateRx(asn_t* asnTimestamp) {
   
   INTERRUPT_DECLARATION();
   DISABLE_INTERRUPTS();
   
   // increment usage statistics
   if (schedule_vars.currentScheduleEntry->numRx==0xFF) {
  	  openserial_printInfo(COMPONENT_SCHEDULE, ERR_TEST_RESET_RX, (errorparameter_t)schedule_vars.currentScheduleEntry->slotOffset, (errorparameter_t)schedule_vars.currentScheduleEntry->numRx);
   }
   schedule_vars.currentScheduleEntry->numRx++;

   // update last used timestamp
   memcpy(&(schedule_vars.currentScheduleEntry->lastUsedAsn), asnTimestamp, sizeof(asn_t));
   
   ENABLE_INTERRUPTS();
}

/**
\brief Indicate the transmission of a packet.
*/
void schedule_indicateTx(asn_t* asnTimestamp, bool succesfullTx) {
   
   INTERRUPT_DECLARATION();
   DISABLE_INTERRUPTS();
   
   // increment usage statistics
   if (schedule_vars.currentScheduleEntry->numTx==0xFF) {
	  openserial_printInfo(COMPONENT_SCHEDULE, ERR_TEST_RESET_TX, (errorparameter_t)schedule_vars.currentScheduleEntry->slotOffset, (errorparameter_t)schedule_vars.currentScheduleEntry->numTxACK);
      schedule_vars.currentScheduleEntry->numTx=0;
      schedule_vars.currentScheduleEntry->numTxACK=0;
   }
   schedule_vars.currentScheduleEntry->numTx++;
   if (succesfullTx==TRUE) {
      schedule_vars.currentScheduleEntry->numTxACK++;
   }

   // update last used timestamp
   memcpy(&schedule_vars.currentScheduleEntry->lastUsedAsn, asnTimestamp, sizeof(asn_t));

   // update this backoff parameters for shared slots
   if (schedule_vars.currentScheduleEntry->shared==TRUE) {
      if (succesfullTx==TRUE) {
         // reset backoffExponent
         schedule_vars.backoffExponent = MINBE-1;
         // reset backoff
         schedule_vars.backoff         = 0;
      } else {
         // increase the backoffExponent
         if (schedule_vars.backoffExponent<MAXBE) {
            schedule_vars.backoffExponent++;
         }
         // set the backoff to a random value in [0..2^BE]
         schedule_vars.backoff         = openrandom_get16b()%(1<<schedule_vars.backoffExponent);
      }
   }
   
   ENABLE_INTERRUPTS();
}

//=========================== private =========================================

/**
\pre This function assumes interrupts are already disabled.
*/
void schedule_resetEntry(scheduleEntry_t* e) {
   e->slotOffset             = 0;
   e->type                   = CELLTYPE_OFF;
   e->shared                 = FALSE;
   e->channelOffset          = 0;

   e->neighbor.type          = ADDR_NONE;
   memset(&e->neighbor.addr_64b[0], 0x00, sizeof(e->neighbor.addr_64b));

   e->numRx                  = 0;
   e->numTx                  = 0;
   e->numTxACK               = 0;
   e->lastUsedAsn.bytes0and1 = 0;
   e->lastUsedAsn.bytes2and3 = 0;
   e->lastUsedAsn.byte4      = 0;
   e->trackID                = 0;
   e->bundleID               = 0;
   e->bier                   = FALSE;
   e->bierDoNotSend          = FALSE;
   e->next                   = NULL;
   e->trackID                = 0;
   e->bundleID               = 0;
}
