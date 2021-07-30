#ifndef USER_HPP
#define USER_HPP

#include <util.hpp>

#include <aws/iam/IAMClient.h>
#include <aws/iam/model/CreateUserRequest.h>
#include <aws/iam/model/CreateUserResult.h>


auto CreateUser(const std::string& userName)
{
  bool flag = false;
  Aws::SDKOptions options;

  Aws::InitAPI(options);
  {
    Aws::IAM::IAMClient iam;

    Aws::IAM::Model::CreateUserRequest create_request;
    create_request.SetUserName(userName);

    auto create_outcome = iam.CreateUser(create_request);
    if (!create_outcome.IsSuccess())
    {
      std::cout << "Error creating IAM user " << userName << ":" << create_outcome.GetError().GetMessage() << std::endl;
    }
    else
    {
      std::cout << "Successfully created IAM user " << userName << std::endl;
      flag = true;
    }
  }
  
  Aws::ShutdownAPI();

  return ((flag) ? 0 : -1);
}

#endif