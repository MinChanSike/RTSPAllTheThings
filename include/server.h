// Copyright 2016 Etix Labs
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include <gst/rtsp-server/rtsp-server.h>
#include <memory>
#include <string>

#define DEFAULT_USERNAME ""
#define DEFAULT_PASSWORD ""
#define DEFAULT_ROUTE "/live.sdp"
#define DEFAULT_ADDRESS "0.0.0.0"
#define DEFAULT_PORT "8554"
#define DEFAULT_INPUT ""
#define DEFAULT_FRAMERATE "25"
#define DEFAULT_WIDTH "1280"
#define DEFAULT_HEIGHT "720"

typedef struct s_config {
  // Server config
  std::string username;
  std::string password;
  std::string route;
  std::string address;
  std::string port;

  // Input
  std::string input;

  // Encoding
  std::string framerate;
  std::pair<std::string, std::string> scale;
} t_config;

typedef struct s_server {
  GMainLoop *loop;
  GstRTSPServer *server;
  GstRTSPMountPoints *mounts;
  GstRTSPMediaFactory *factory;
  GstRTSPAuth *auth;
  GstRTSPToken *token;
  gchar *basic;
  std::shared_ptr<t_config> config;
} t_server;

void init(t_server *serv);
// Config
bool parse_args(std::shared_ptr<t_config> config, int argc, char **argv);
void parse_env(std::shared_ptr<t_config> config);
// Server
void server_init(t_server *serv);
int server_launch(t_server *serv);
// Pipeline
std::string create_pipeline(std::shared_ptr<t_config> config);
