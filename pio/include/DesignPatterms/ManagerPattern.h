#include <map>      // Header file include for map
using namespace std;// STL containers are defined in std namespace


class Terminal_Message
      {
      public:
            int Get_Terminal_Id() const;
      };


class Terminal
      {
      public:


            Terminal(int terminal_Id, int type);

            void Handle_Message(const Terminal_Message* pMsg);

            int Get_Terminal_Id() const;
      };


class Terminal_Manager
      {
      typedef map<int, Terminal*> Terminal_Map;

      Terminal_Map m_terminal_Map;

      public:

            enum Status { FAILURE, SUCCESS };


            Status Add_Terminal(int terminal_Id, int type)
                  {
                  Status status;

                  // Check if the terminal is already present in the map. count()
                  // returns the total number of entries that are keyed by terminal_Id
                  if (m_terminal_Map.count(terminal_Id) == 0)
                        {
                        // count() returned zero, so no entries are present in the map
                        Terminal* pTerm = new Terminal(terminal_Id, type);

                        // Since map overloads the array operator [ ], it gives 
                        // the illusion of indexing into an array. The following
                        // line makes an entry into the map
                        m_terminal_Map[terminal_Id] = pTerm;

                        status = SUCCESS;
                        }
                  else
                        {
                        // count() returned a non zero value, so the terminal is already
                        // present.
                        status = FAILURE;
                        }

                  return status;
                  }


            Status Remove_Terminal(int terminal_Id)
                  {
                  Status status;
                  // Check if the terminal is present
                  if (m_terminal_Map.count(terminal_Id) == 1)
                        {
                        // Save the pointer that is being deleted from the map
                        Terminal* pTerm = m_terminal_Map[terminal_Id];

                        // Erase the entry from the map. This just frees up the memory for
                        // the pointer. The actual object is freed up using delete
                        m_terminal_Map.erase(terminal_Id);
                        delete pTerm;

                        status = SUCCESS;
                        }
                  else
                        {
                        status = FAILURE;
                        }

                  return status;
                  }


            Terminal* Find_Terminal(int terminal_Id)
                  {
                  Terminal* pTerm;
                  if (m_terminal_Map.count(terminal_Id) == 1)
                        {
                        pTerm = m_terminal_Map[terminal_Id];
                        }
                  else
                        {
                        pTerm = NULL;
                        }

                  return pTerm;
                  }


            void Handle_Message(const Terminal_Message* pMsg)
                  {
                  int terminal_Id = pMsg->Get_Terminal_Id();

                  Terminal* pTerm;

                  pTerm = Find_Terminal(terminal_Id);

                  if (pTerm)
                        {
                        pTerm->Handle_Message(pMsg);
                        }
                  }
      };