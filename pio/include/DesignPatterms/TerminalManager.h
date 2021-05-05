class TerminalManager : public ResourceManager
  {
  Terminal* terminals[MAX_TERMINALS];
  public:
    void handleMessage(Msg* pMsg)
      {
      switch (pMsg->getType())
        {
          case CREATE_TERMINAL:
            terminals[pMsg->getTerminalId()] = new Terminal(pMsg->getTerminalId());
            break;
          case DELETE_TERMINAL:
            delete terminals[pMsg->getTerminalId()];
            break;
          case RUN_DIAGNOSTICS:
            status = terminals[pMsg->getTerminalId()]->handleRunDiagnostics();
            break;
          case PERFORM_SWITCHOVER:
            status1 = terminals[pMsg->getTerminalId1()]->handleOutOfService();
            status2 = terminals[pMsg->getTerminalId2()]->handleInService();
            break;
        }
      }
  };

class Terminal
  {
  TerminalId terminalId;
  public:
    Terminal(TerminalID terminalId);
    ~Terminal();
    Status handleRunDiagnostics();
    Status handleOutOfService();
    Status handleInService();
  };