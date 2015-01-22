#ifndef COVERAGE_PLUGIN_H
#define COVERAGE_PLUGIN_H

#include <time.h>

namespace coverage {

    enum Status {
        Calculated,
        Uncovered,
        Covered,
        Unreachable
    };

    typedef int RunId;

    namespace interface {

        RunId add_run(const char* description, time_t timestamp);
        void remove_run(RunId id);
        void set_run_description(RunId id, const char* description);

        void set_project_description(const char* category, const char* description);

        void set_node_coverage(RunId result, int node, unsigned int coverage_count);
        void set_node_comment(int node, const char* message);
        void set_node_status(int node, Status status);
    }


    namespace analyser {
        void analyse_buffer(void* buffer, size_t size);
    }

    namespace collector {
        void set_project_data(void* buffer, size_t size);
        void get_project_data(void* buffer, size_t size);

        void set_source_buffer(void* buffer, size_t size);
        void send_buffer(void* buffer, size_t size);
        void receive_buffer(void* buffer, size_t size);
    }
}

#endif
