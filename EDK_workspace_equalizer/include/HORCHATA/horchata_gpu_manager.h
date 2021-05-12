
#ifndef INCLUDE_HORCHATA_GPUMANAGER_H_
#define INCLUDE_HORCHATA_GPUMANAGER_H_ 1

#include <EDK3/dev/gpumanager.h>


namespace HORCHATA {

	class GPUManager : public EDK3::dev::GPUManager {

		virtual void newBuffer(EDK3::ref_ptr<EDK3::dev::Buffer>* output) override;

	};


}






#endif