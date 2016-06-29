#include "opendefs.h"
#include "otf.h"
#include "neighbors.h"
#include "sixtop.h"
#include "scheduler.h"

//=========================== variables =======================================

//=========================== prototypes ======================================

void otf_addCell_task(void);
void otf_removeCell_task(void);

//=========================== public ==========================================

void otf_init(void) {
}

void otf_notif_addedCell(void) {
   scheduler_push_task(otf_addCell_task,TASKPRIO_OTF);
}

void otf_notif_removedCell(void) {
   scheduler_push_task(otf_removeCell_task,TASKPRIO_OTF);
}

//=========================== private =========================================

void otf_addCell_task(void) {
   uint8_t              parentIdxArr[MAXPREFERENCE];
   open_addr_t          neighbor;
   uint8_t              foundNeighbor;

   // get preferred parent
   foundNeighbor = neighbors_getPreferredParentEui64(parentIdxArr);
   neighbors_getParent(&neighbor, ADDR_64B, parentIdxArr[0]);
   if (foundNeighbor==0) {
      return;
   }

   sixtop_setHandler(SIX_HANDLER_OTF);
   // call sixtop
   sixtop_request(
      IANA_6TOP_CMD_ADD,
      &neighbor,
      1
   );
}

void otf_removeCell_task(void) {
   uint8_t              parentIdxArr[MAXPREFERENCE];
   open_addr_t          neighbor;
   uint8_t              foundNeighbor;
   
   // get preferred parent
   foundNeighbor = neighbors_getPreferredParentEui64(parentIdxArr);
   neighbors_getParent(&neighbor, ADDR_64B, parentIdxArr[0]);
   if (foundNeighbor==0) {
      return;
   }
   
   sixtop_setHandler(SIX_HANDLER_OTF);
   // call sixtop
   sixtop_request(
      IANA_6TOP_CMD_DELETE,
      &neighbor,
      1
   );
}