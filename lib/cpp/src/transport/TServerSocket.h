/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements. See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership. The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License. You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#ifndef _THRIFT_TRANSPORT_TSERVERSOCKET_H_
#define _THRIFT_TRANSPORT_TSERVERSOCKET_H_ 1

#include "TServerTransport.h"
#include <boost/shared_ptr.hpp>

namespace apache { namespace thrift { namespace transport {

class TSocket;

/**
 * Server socket implementation of TServerTransport. Wrapper around a unix
 * socket listen and accept calls.
 *
 */
class TServerSocket : public TServerTransport {
 public:
  TServerSocket(int port);
  TServerSocket(std::string host, int port);
  TServerSocket(int port, int sendTimeout, int recvTimeout);

  ~TServerSocket();

  void setSendTimeout(int sendTimeout);
  void setRecvTimeout(int recvTimeout);

  void setRetryLimit(int retryLimit);
  void setRetryDelay(int retryDelay);

  void setTcpSendBuffer(int tcpSendBuffer);
  void setTcpRecvBuffer(int tcpRecvBuffer);

  void listen();
  void close();

  void interrupt();

 protected:
  boost::shared_ptr<TTransport> acceptImpl();

 private:
  void init(int port);

  std::string host_;
  int port_;
  int serverSocket_;
  int acceptBacklog_;
  int sendTimeout_;
  int recvTimeout_;
  int retryLimit_;
  int retryDelay_;
  int tcpSendBuffer_;
  int tcpRecvBuffer_;

  int intSock1_;
  int intSock2_;
};

}}} // apache::thrift::transport

#endif // #ifndef _THRIFT_TRANSPORT_TSERVERSOCKET_H_
