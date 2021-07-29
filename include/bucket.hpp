#ifndef BKT_HPP
#define BKT_HPP

#include <util.hpp>

#include <aws/s3/model/CreateBucketRequest.h>
#include <aws/s3/model/DeleteBucketRequest.h>
#include <aws/s3/model/BucketLocationConstraint.h>

auto CreateBucket(const std::string& accessKey, const std::string& secretKey, const std::string& bucketName)
{
  auto flag = false;
  Aws::SDKOptions options;

  Aws::InitAPI(options);
  {
    std::cout << "Client Created\n";

    auto client = InitializeClient(
      Aws::String(accessKey.c_str(), accessKey.size()),
      Aws::String(secretKey.c_str(), secretKey.size())
    );

    std::cout << "Client Initialized\n";

    Aws::S3::Model::CreateBucketRequest request;
    request.SetBucket(Aws::String(bucketName.c_str(), bucketName.size()));
    request.SetObjectLockEnabledForBucket(true);

    auto outcome = client.CreateBucket(request);

    if (!outcome.IsSuccess())
    {
      auto err = outcome.GetError();
      std::cout << "Error: CreateBucket: " << err.GetExceptionName() << ": " << err.GetMessage() << "\n";
      goto end;
    }

    std::cout << "Create Bucket: Succedded\n";
    flag = true;
  }

end:

  Aws::ShutdownAPI(options);

  return flag;
}

bool DeleteBucket(const std::string& accessKey, const std::string& secretKey, const std::string& bucketName)
{
  auto flag = false;
  Aws::SDKOptions options;

  Aws::InitAPI(options);
  {
    auto client = InitializeClient(
      Aws::String(accessKey.c_str(), accessKey.size()),
      Aws::String(secretKey.c_str(), secretKey.size())
    );

    Aws::S3::Model::DeleteBucketRequest request;
    request.SetBucket(Aws::String(bucketName.c_str(), bucketName.size()));

    auto outcome = client.DeleteBucket(request);

    if (!outcome.IsSuccess())
    {
      auto err = outcome.GetError();
      std::cout << "Error: DeleteBucket: " <<err.GetExceptionName() << ": " << err.GetMessage() << std::endl;

      goto end;
    }

    std::cout << "Bucket: '" << bucketName << "' was deleted.\n";
    flag = true;
  }

end:
  
  ShutdownAPI(options);
  return flag;
}

#endif