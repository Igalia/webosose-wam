// Copyright (c) 2014-2018 LG Electronics, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0

#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#include <QtCore/QList>
#include <string>

#include "BlinkWebProcessManager.h"
#include "WebPageBlink.h"
#include "WebAppBase.h"
#include "WebAppManagerUtils.h"
#include "LogManager.h"
#include "BlinkWebView.h"
#include "BlinkWebViewProfileHelper.h"
#include "WebProcessManager.h"

uint32_t BlinkWebProcessManager::getWebProcessPID(const WebAppBase* app) const
{
    return static_cast<WebPageBlink*>(app->page())->renderProcessPid();
}

QJsonObject BlinkWebProcessManager::getWebProcessProfiling()
{
    QJsonObject reply;
    QJsonArray processArray;
    QJsonObject processObject;
    uint32_t pid;
    std::vector<uint32_t> processIdList;

    std::multimap<uint32_t, std::string> runningAppList;
    std::list<const WebAppBase*> running = runningApps();
    for (std::list<const WebAppBase*>::iterator it = running.begin(); it != running.end(); ++it) {
        WebAppBase* app = findAppById((*it)->appId());
        pid = getWebProcessPID(app);

        auto search = std::find (processIdList.begin(), processIdList.end(), pid);
        if (search == processIdList.end())
            processIdList.push_back(pid);

        runningAppList.insert(make_pair(pid, app->appId()));
    }

    WebAppBase* containerApp = getContainerApp();
    if (containerApp) {
        pid = getWebProcessPID(containerApp);
        auto search = std::find (processIdList.begin(), processIdList.end(), pid);
        if (search == processIdList.end())
            processIdList.push_back(pid);

        runningAppList.insert(make_pair(pid, containerApp->appId()));
    }

    for (unsigned int id = 0; id < processIdList.size(); id++) {
        QJsonObject appObject;
        QJsonArray appArray;
        pid = processIdList.at(id);

        processObject["pid"] = QString::number(pid);
        //processObject["webProcessSize"] = getWebProcessMemSize(pid); // TODO : Uncommnet during replacement of QJson
        //starfish-surface is note used on Blink
        processObject["tileSize"] = 0;
        std::vector<std::string> processApp;
        auto range = runningAppList.equal_range(pid);
        for (auto itr = range.first; itr != range.second; ++itr) {
            processApp.push_back(itr->second);
        }

        for (unsigned app = 0; app < processApp.size(); app++) {
            //appObject["id"] = processApp.at(app); // TODO : Uncommnet after porting of QJsonObject
            appArray.append(appObject);
        }
        processObject["runningApps"] = appArray;
        processArray.append(processObject);
    }

    reply["WebProcesses"] = processArray;
    reply["returnValue"] = true;
    return reply;
}

void BlinkWebProcessManager::deleteStorageData(const std::string& identifier)
{
#if 0
    std::list<const WebAppBase*> runningAppList = runningApps();
    if (!runningAppList.empty()) {
        runningAppList.front()->page()->deleteWebStorages(identifier);
        return;
    }

    WebAppBase* containerApp = getContainerApp();
    if (containerApp) {
        containerApp->page()->deleteWebStorages(identifier);
        return;
    }

    BlinkWebView* webview = new BlinkWebView();
    if (webview) {
        webview->DeleteWebStorages(identifier.toStdString());
        delete webview;
    }
#endif
}

uint32_t BlinkWebProcessManager::getInitialWebViewProxyID() const
{
    return 0;
}

void BlinkWebProcessManager::clearBrowsingData(const int removeBrowsingDataMask)
{
    BlinkWebViewProfileHelper::clearBrowsingData(removeBrowsingDataMask);
}

int BlinkWebProcessManager::maskForBrowsingDataType(const char* type)
{
    return BlinkWebViewProfileHelper::maskForBrowsingDataType(type);
}
