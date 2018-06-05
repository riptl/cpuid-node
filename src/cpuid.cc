#include <nan.h>
#include <libcpuid.h>

// Set feature Macro
#define SF(jsName, cName) features->Set(Nan::New("jsName").ToLocalChecked(), Nan::New(cpuData.flags[CPU_FEATURE_ ## cName]))

using namespace v8;

static const char* mapVendor(cpu_vendor_t vendor) {
	switch(vendor) {
		case VENDOR_INTEL:
			return "intel";

		case VENDOR_AMD:
			return "amd";

		case VENDOR_CYRIX:
			return "cyrix";

		case VENDOR_NEXGEN:
			return "nexgen";

		case VENDOR_TRANSMETA:
			return "transmeta";

		case VENDOR_UMC:
			return "umc";

		case VENDOR_CENTAUR:
			return "idt";

		case VENDOR_RISE:
			return "rise";

		case VENDOR_SIS:
			return "sis";

		case VENDOR_NSC:
			return "nsc";

		default:
			return "unknown";
	}
}


static void fillFeatures(Handle<Object> features, cpu_id_t& cpuData) {
	SF(fpu, FPU);
	SF(virtualModeExtension, VME);
	SF(debuggingExtension, DE);
	SF(pageSizeExtension, PSE);
	SF(timeStampCounter, TSC);
	SF(modelSpecificRegisters, MSR);
	SF(physicalAddressExtension, PAE);
	SF(machineCheckException, MCE);
	SF(cx8Instruction, CX8);
	SF(apic, APIC);
	SF(mtrr, MTRR);
	SF(sepInstructions, SEP);
	SF(pageGlobalEnable, PGE);
	SF(machineCheckArchitecture, MCA);
	SF(cmovInstructions, CMOV);
	SF(pageAttributeTable, PAT);
	SF(pageAddressExtension36bit, PSE36);
	SF(processorSerialNumber, PN);
	SF(clflushInstruction, CLFLUSH);
	SF(debugStore, DTS);
	SF(acpi, ACPI);
	SF(mmx, MMX);
	SF(fxsrInstructions, FXSR);
	SF(sse, SSE);
	SF(sse2, SSE2);
	SF(selfSnoop, SS);
	SF(hyperthreading, HT);
	SF(thermalMonitor, TM);
	SF(ia64, IA64);
	SF(pendingBreakEnable, PBE);
	SF(sse3, PNI);
	SF(pclmulInstruction, PCLMUL);
	SF(debugStore64bit, DTS64);
	SF(monitor, MONITOR);
	SF(cplDebugStore, DS_CPL);
	SF(virtualization, VMX);
	SF(saferModeException, SMX);
	SF(enhancedSpeedStep, EST);
	SF(thermalMonitor2, TM2);
	SF(ssse3Instructions, SSSE3);
	SF(contextId, CID);
	SF(cx16Instruction, CX16);
	SF(tprDisable, XTPR);
	SF(stpmDisable, XTPR);
	SF(pdcm, PDCM);
	SF(directCacheAccess, DCA);
	SF(sse41, SSE4_1);
	SF(sse42, SSE4_2);
	SF(syscallInstructions, SYSCALL);
	SF(executeDisableBit, XD);
	SF(movbeInstruction, MOVBE);
	SF(popcntInstruction, POPCNT);
	SF(aesInstructions, AES);
	SF(xsaveInstructions, XSAVE);
	SF(osxsaveInstruction, OSXSAVE);
	SF(avx, AVX);
	SF(mmxExt, MMXEXT);
	SF(amd3dNow, 3DNOW);
	SF(amd3dNowExt, 3DNOWEXT);
	SF(noExecuteBit, NX);
	SF(fxsrOptimizations, FXSR_OPT);
	SF(rdtscpInstruction, RDTSCP);
	SF(em64t, LM);
	SF(x86_64, LM);
	SF(lahf64bit, LAHF_LM);
	SF(cmpLegacy, CMP_LEGACY);
	SF(secureVirtualMachine, SVM);
	SF(lzcntInstruction, ABM);
	SF(misalignedSSE, MISALIGNSSE);
	SF(sse4a, SSE4A);
	SF(amd3dNowPrefetch, 3DNOWPREFETCH);
	SF(osVisibleWorkaround, OSVW);
	SF(instructionBasedSampling, IBS);
	SF(sse5, SSE5);
	SF(skinitInstructions, SKINIT);
	SF(watchdogTimer, WDT);
	SF(temperatureSensor, TS);
	SF(frequencyIDControl, FID);
	SF(voltageIDControl, VID);
	SF(thermtrip, TTP);
	SF(amdThermalControl, TM_AMD);
	SF(softwareThermalControl, STC);
	SF(multiplierSteps100mhz, 100MHZSTEPS);
	SF(hardwarePState, HWPSTATE);
	SF(constantTSCTicks, CONSTANT_TSC);
	SF(xop, XOP);
	SF(fma3, FMA3);
	SF(fma4, FMA4);
	SF(trailingBitManipulation, TBM);
	SF(f16c, F16C);
	SF(readRandomNumber, RDRAND);
	SF(x2apic, X2APIC);
	SF(corePerformanceBoost, CPB);
	SF(aperfMperf, APERFMPERF);
	SF(processorFeedbackInterface, PFI);
	SF(processorAccumulator, PA);
	SF(avx2, AVX2);
	SF(bmi1, BMI1);
	SF(bmi2, BMI2);
	SF(hardwareLockElision, HLE);
	SF(avx512f, AVX512F);
	SF(avx512dq, AVX512DQ);
	SF(avx512pf, AVX512PF);
	SF(avx512er, AVX512ER);
	SF(avx512cd, AVX512CD);
	SF(sha, SHA_NI);
	SF(avx512bw, AVX512BW);
	SF(avx512vl, AVX512VL);
	SF(sgx, SGX);
	SF(readRandomNumberSeed, RDSEED);
	SF(adx, ADX);
}

static void fillCache(Handle<Object> cache, cpu_id_t& cpuData) {
	Local<Object> l1 = Nan::New<Object>();
	cache->Set(Nan::New("l1").ToLocalChecked(), l1);

	l1->Set(Nan::New("data").ToLocalChecked(), Nan::New(cpuData.l1_data_cache));
	l1->Set(Nan::New("instruction").ToLocalChecked(), Nan::New(cpuData.l1_instruction_cache));
	l1->Set(Nan::New("associativity").ToLocalChecked(), Nan::New(cpuData.l1_assoc));
	l1->Set(Nan::New("cacheline").ToLocalChecked(), Nan::New(cpuData.l1_cacheline));

	Local<Object> l2 = Nan::New<Object>();
	cache->Set(Nan::New("l2").ToLocalChecked(), l2);

	l2->Set(Nan::New("size").ToLocalChecked(), Nan::New(cpuData.l2_cache));
	l2->Set(Nan::New("associativity").ToLocalChecked(), Nan::New(cpuData.l2_assoc));
	l2->Set(Nan::New("cacheline").ToLocalChecked(), Nan::New(cpuData.l2_cacheline));

	Local<Object> l3 = Nan::New<Object>();
	cache->Set(Nan::New("l3").ToLocalChecked(), l3);

	l3->Set(Nan::New("size").ToLocalChecked(), Nan::New(cpuData.l3_cache));
	l3->Set(Nan::New("associativity").ToLocalChecked(), Nan::New(cpuData.l3_assoc));
	l3->Set(Nan::New("cacheline").ToLocalChecked(), Nan::New(cpuData.l3_cacheline));
}

static void fillId(Handle<Object> id, cpu_id_t& cpuData) {
	id->Set(Nan::New("family").ToLocalChecked(), Nan::New(cpuData.family));
	id->Set(Nan::New("model").ToLocalChecked(), Nan::New(cpuData.model));
	id->Set(Nan::New("stepping").ToLocalChecked(), Nan::New(cpuData.stepping));
	id->Set(Nan::New("extFamily").ToLocalChecked(), Nan::New(cpuData.ext_family));
	id->Set(Nan::New("extModel").ToLocalChecked(), Nan::New(cpuData.ext_model));
}



NAN_METHOD(GetCPUID) {
	if(!cpuid_present()) {
		return Nan::ThrowError("CPUID instruction not available");
	}

	cpu_raw_data_t raw;
	if(cpuid_get_raw_data(&raw) < 0) {
		return Nan::ThrowError("Could not execute CPUID");
	}

	cpu_id_t cpuData;
	if(cpu_identify(&raw, &cpuData) < 0) {
		return Nan::ThrowError("Could not parse CPUID data");
	}

	Local<Object> data = Nan::New<Object>();
	data->Set(Nan::New("vendorName").ToLocalChecked(), Nan::New(cpuData.vendor_str).ToLocalChecked());
	data->Set(Nan::New("vendor").ToLocalChecked(), Nan::New(mapVendor(cpuData.vendor)).ToLocalChecked());
	data->Set(Nan::New("vendorNumber").ToLocalChecked(), Nan::New(cpuData.vendor));
	data->Set(Nan::New("brand").ToLocalChecked(), Nan::New(cpuData.brand_str).ToLocalChecked());
	data->Set(Nan::New("codeName").ToLocalChecked(), Nan::New(cpuData.cpu_codename).ToLocalChecked());
	data->Set(Nan::New("physicalCores").ToLocalChecked(), Nan::New(cpuData.num_cores));
	data->Set(Nan::New("logicalCores").ToLocalChecked(), Nan::New(cpuData.num_logical_cpus));
	data->Set(Nan::New("totalCores").ToLocalChecked(), Nan::New(cpuData.total_logical_cpus));
	data->Set(Nan::New("clockSpeed").ToLocalChecked(), Nan::New(cpu_clock()));

	Local<Object> features = Nan::New<Object>();
	data->Set(Nan::New("features").ToLocalChecked(), features);
	fillFeatures(features, cpuData);

	Local<Object> cache = Nan::New<Object>();
	data->Set(Nan::New("cache").ToLocalChecked(), cache);
	fillCache(cache, cpuData);

	Local<Object> id = Nan::New<Object>();
	data->Set(Nan::New("id").ToLocalChecked(), id);
	fillId(id, cpuData);

	info.GetReturnValue().Set(data);
}

NAN_MODULE_INIT(InitAll) {
	Nan::Set(target, Nan::New("getCPUID").ToLocalChecked(),
		Nan::GetFunction(Nan::New<FunctionTemplate>(GetCPUID)).ToLocalChecked());
}

NODE_MODULE(cpuid, InitAll)
