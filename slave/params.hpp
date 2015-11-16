#pragma once

#include <stddef.h>

#include <mesos/mesos.pb.h>

namespace stats {
  namespace params {

    /**
     * Input settings
     */

    // The host to listen on. Should stay with "localhost" except in ip-per-container environments.
    const std::string LISTEN_HOST = "listen_host";
    const std::string LISTEN_HOST_DEFAULT = "localhost";

    // The mode to use for assigning containers to listen ports.
    const std::string LISTEN_PORT_MODE = "listen_port_mode";

    // Listens to only a single port across the slave. Only advisable in ip-per-container environments.
    // In this mode, listen_port must be non-zero.
    const std::string LISTEN_PORT_MODE_SINGLE = "single";
    const std::string LISTEN_PORT = "listen_port";
    const size_t LISTEN_PORT_DEFAULT = 0;

    // Listens to ports in the OS-defined ephemeral port range which are then dynamically assigned to containers.
    // See /proc/sys/net/ipv4/ip_local_port_range and/or sysctl's net.ipv4.ip_local_port_range.
    const std::string LISTEN_PORT_MODE_EPHEMERAL = "ephemeral";

    // Listens to a specified range of ports which are then dynamically assigned to containers.
    // In this mode, listen_port_start/listen_port_end must be non-zero.
    const std::string LISTEN_PORT_MODE_RANGE = "range";
    const std::string LISTEN_PORT_START = "listen_port_start";
    const size_t LISTEN_PORT_START_DEFAULT = 0;
    const std::string LISTEN_PORT_END = "listen_port_end";
    const size_t LISTEN_PORT_END_DEFAULT = 0;

    // Default to ephemeral unless/until ip-per-container becomes common.
    const std::string LISTEN_PORT_MODE_DEFAULT = LISTEN_PORT_MODE_EPHEMERAL;

    enum PortMode {
      UNKNOWN_MODE, SINGLE_PORT, EPHEMERAL_PORTS, PORT_RANGE
    };
    PortMode to_port_mode(const std::string& param);

    /**
     * Output settings
     */

    // The host to send to. Should be the endpoint for tasks in the monitoring framework.
    const std::string DEST_HOST = "dest_host";
    const std::string DEST_HOST_DEFAULT = "statsd.monitoring.mesos";

    // The port to send to.
    const std::string DEST_PORT = "dest_port";
    const size_t DEST_PORT_DEFAULT = 8125;

    // The MTU to enforce for sent packets.
    const std::string DEST_UDP_MAX_BYTES = "dest_udp_max_bytes";
    const int DEST_UDP_MAX_BYTES_DEFAULT = 512;

    // Whether to annotate output with datadog tags about originating containers.
    const std::string ANNOTATIONS = "annotations";
    const bool ANNOTATIONS_DEFAULT = true;

    std::string get_str(const mesos::Parameters& parameters, const std::string& key, const std::string& default_value);
    size_t get_uint(const mesos::Parameters& parameters, const std::string& key, size_t default_value);
    bool get_bool(const mesos::Parameters& parameters, const std::string& key, bool default_value);
  }
}
