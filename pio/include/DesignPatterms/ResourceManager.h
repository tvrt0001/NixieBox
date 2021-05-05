#include <queue>           // STL header file for queue
#include <map>             // Header file for map
using namespace std;       // Specify that we are using the std namespace

// Resource Id: A unique id assigned to every resource 
typedef int ResourceId;

class ResourceManager
   {
   // Declaring the type for a queue. Here we are specifying
   // a queue of Resource pointers organized as a linked list.
   typedef queue<Resource*>, list<Resource*> > FreeResourceQueue;
   FreeResourceQueue m_freeResourceQueue;

   // Map is used to keep track of the busy resources.
   typedef map <Resource*, ResourceId> BusyResourceMap;
   BusyResourceMap m_busyResourceMap;
   public:

      ResourceManager(int resourceCount, Resource* resourceArray)
         {
         // Add all the resources that have been specified at construction time
         for (int i = 0; i < resourceCount; i++)
            {
            Add(resourceArray[i]);
            }
         }
      // Allocate a free resource by removing it from the
      // the free resource queue. Returns NULL if no resource is found
      Resource* Allocate()
         {
         Resource* pResource = NULL;

         // Check if any free resources are available.
         if (!m_freeResourceQueue.empty())
            {
            // Queue is not empty so get a pointer to the
            // first resource in the queue
            pResource = m_freeResourceQueue.front();

            // Now remove the pointer from the free resource queue
            m_freeResourceQueue.pop();

            // Next step is to add the resource to the busy map ...
            // Obtain the resource id
            ResourceId resId = pResource->GetResourceId();

            // Make sure that the resource is not already present in the map
            if (m_busyResourceMap.count(resId) == 0)
               {
               m_busyResourceMap[resId] = pResource;
               }
            }
         return pResource;
         }

      // Free a resource by adding it back into the free resource list
      void Free(Resource* pResource)
         {
         // Obtain the resource Id
         ResourceId resId = pResource->GetResourceId();

         // Remove the resource from the busy resource map
         m_busyResourceMap.erase(resId);

         // Insert the resource at the end of the free queue
         m_freeResourceQueue.push(pResource);
         }

      // Obtain the total count of free resources
      int GetFreeResourceCount() const
         {
         return m_freeResourceQueue.size();
         }

      int GetBusyResourceCount() const
         {
         return m_busyResourceMap.size();
         }

      // Adding a new resource to the resource manager.
      void Add(Resource* pResource)
         {
         // A new resource is assumed to be free, hence it is 
         // added to the free queue
         m_freeResourceQueue.push(pResource);
         }

      // Remove the resource from the resource manager
      void Remove(Resource* pResource)
         {
         // Obtain the resource id
         ResourceId resId = pResource->GetResourceId();

         // Check if the resource is present in the map
         // i.e. the resource is currently busy
         if (m_busyResourceMap.count(resId))
            {
            // This resource is currently in use, so inform
            // the Resource object about this release. Resource
            // will inform the application about the forced release
            pResource->HandleForcedRelease();

            // Remove the resource from the busy resource map
            m_busyResourceMap.erase(resId);
            }
         else
            {
            // remove the pointer from the free resource queue
            m_freeResourceQueue.erase(resId);
            }
         }
   };