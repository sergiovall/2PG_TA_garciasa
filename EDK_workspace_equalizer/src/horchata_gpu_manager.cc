#include <HORCHATA/horchata_gpu_manager.h>
#include <HORCHATA/horchata_buffer.h>

void HORCHATA::GPUManager::newBuffer(EDK3::ref_ptr<EDK3::dev::Buffer>* output) {

	output->allocT<HORCHATA::Buffer>();

}

