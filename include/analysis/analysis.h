#ifndef REDSHOW_ANALYSIS_ANALYSIS_H
#define REDSHOW_ANALYSIS_ANALYSIS_H

#include <string>

#include "redshow.h"
#include "common/map.h"
#include "binutils/cubin.h"
#include "operation/operation.h"
#include "operation/kernel.h"

namespace redshow {

struct Trace {
  Kernel kernel;
};

class Analysis {
 public:
  Analysis(redshow_analysis_type_t type) : _type(type) {}

  virtual void lock() {
    this->_lock.lock();
  }

  virtual void unlock() {
    this->_lock.unlock();
  }
  
  // Coarse-grained
  virtual void op_callback(OperationPtr operation) = 0;

  // Fine-grained
  virtual void analysis_begin(u32 cpu_thread, i32 kernel_id, u32 cubin_id, u32 mod_id) = 0;

  virtual void analysis_end(u32 cpu_thread, i32 kernel_id) = 0;

  virtual void block_enter(const ThreadId &thread_id) = 0;

  virtual void block_exit(const ThreadId &thread_id) = 0;

  virtual void unit_access(i32 kernel_id, const ThreadId &thread_id, const AccessKind &access_kind,
                           u64 memory_op_id, u64 pc, u64 value, u64 addr, u32 stride, u32 index,
                           bool read) = 0;

  // Flush
  virtual void flush_thread(u32 cpu_thread, const std::string &output_dir,
                            const LockableMap<u32, Cubin> &cubins, 
                            redshow_record_data_callback_func record_data_callback) = 0;

  virtual void flush(const std::string &output_dir, const LockableMap<u32, Cubin> &cubins, 
                     const Vector<OperationPtr> &operations,
                     redshow_record_data_callback_func record_data_callback) = 0;

  virtual ~Analysis() {}
 
 protected:
  Map<u32, Map<i32, std::shared_ptr<Trace>>> _kernel_trace;

  redshow_analysis_type_t _type;
  std::mutex _lock;
};

}  // namespace redshow

#endif  // REDSHOW_ANALYSIS_ANALYSIS_H