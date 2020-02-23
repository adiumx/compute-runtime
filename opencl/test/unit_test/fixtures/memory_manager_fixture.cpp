/*
 * Copyright (C) 2017-2020 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "opencl/test/unit_test/fixtures/memory_manager_fixture.h"

#include "command_stream/preemption.h"
#include "helpers/hw_helper.h"
#include "os_interface/os_context.h"
#include "opencl/test/unit_test/mocks/mock_csr.h"
#include "opencl/test/unit_test/mocks/mock_memory_manager.h"

using namespace NEO;

void MemoryManagerWithCsrFixture::SetUp() {
    executionEnvironment.setHwInfo(*platformDevices);
    executionEnvironment.prepareRootDeviceEnvironments(1);
    csr = std::make_unique<MockCommandStreamReceiver>(this->executionEnvironment, 0);
    memoryManager = new MockMemoryManager(executionEnvironment);
    executionEnvironment.memoryManager.reset(memoryManager);
    csr->tagAddress = &currentGpuTag;
    auto engine = HwHelper::get(platformDevices[0]->platform.eRenderCoreFamily).getGpgpuEngineInstances()[0];
    auto osContext = memoryManager->createAndRegisterOsContext(csr.get(), engine, 1, PreemptionHelper::getDefaultPreemptionMode(*platformDevices[0]), false);
    csr->setupContext(*osContext);
}

void MemoryManagerWithCsrFixture::TearDown() {
}