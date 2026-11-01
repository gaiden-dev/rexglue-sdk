/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2025 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 *
 * @modified    Rien Gupta, 2026 - Adapted for ReXGlue runtime
 */

#pragma once

#include <memory>

#include <rex/ui/d3d12/d3d12_api.h>
#include <rex/ui/gpu_completion_timeline.h>

namespace rex::ui::d3d12 {

class D3D12GPUCompletionTimeline : public GPUCompletionTimeline {
 public:
  static std::unique_ptr<D3D12GPUCompletionTimeline> Create(ID3D12Device* device);

  D3D12GPUCompletionTimeline(const D3D12GPUCompletionTimeline&) = delete;
  D3D12GPUCompletionTimeline& operator=(const D3D12GPUCompletionTimeline&) = delete;
  D3D12GPUCompletionTimeline(D3D12GPUCompletionTimeline&&) = delete;
  D3D12GPUCompletionTimeline& operator=(D3D12GPUCompletionTimeline&&) = delete;

  ~D3D12GPUCompletionTimeline();

  ID3D12Fence* GetFence() const { return fence_.Get(); }

  using GPUCompletionTimeline::IncrementUpcomingSubmission;

  void UpdateCompletedSubmission() override;

  // If signaling has succeeded, will advance to the next submission.
  HRESULT SignalAndAdvance(ID3D12CommandQueue* queue);

 protected:
  void AwaitSubmissionImpl(uint64_t awaited_submission) override;

 private:
  explicit D3D12GPUCompletionTimeline(ID3D12Fence* const fence) : fence_(fence) {}

  Microsoft::WRL::ComPtr<ID3D12Fence> fence_;
};

}  // namespace rex::ui::d3d12
