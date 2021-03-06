/*
 * Copyright (c) 2009 Mark Liversedge (liversedge@gmail.com)
 *               2015 Vianney Boyer   (vlcvboyer@gmail.com)
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc., 51
 * Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef _GC_VideoWindow_h
#define _GC_VideoWindow_h 1
#include "GoldenCheetah.h"
#include "MeterWidget.h"

// We need to determine what options the user has chosen
// for compiling, which differ for Mac vs Win/Linux
//
// Options are, GC_VIDEO_xxxx where xxxx is one of:
// GC_VIDEO_VLC
// GC_VIDEO_QUICKTIME
// GC_VIDEO_NONE
// GC_VIDEO_QT5
//
// If the user hasn't set one of the above then we determine
// which one should apply !

//----------------------------------------------------------------------
// MAC VIDEO OPTION SETTING
//----------------------------------------------------------------------
#ifdef Q_OS_MAC

// if we aint chosen one or the other then use quicktime
#if !defined GC_VIDEO_QUICKTIME && !defined GC_VIDEO_NONE && !defined GC_VIDEO_QT5 && !defined GC_VIDEO_VLC
#define GC_VIDEO_QUICKTIME
#endif

// but qt5 and vlc are not experimental options !
#if defined GC_VIDEO_VLC
#warning "VLC is supported experimentally on Mac OS X builds of GoldenCheetah"
#endif

// but qt5 *is* supported, but use at your own risk!
#if defined GC_VIDEO_QT5
#warning "QT 5 video is supported experimentally in this version"
#endif

#endif //Q_OS_MAC

//----------------------------------------------------------------------
// LINUX AND WINDOWS
//----------------------------------------------------------------------

#if defined Q_OS_LINUX || defined Q_OS_WIN

// did the user specify location for VLC but not GC_VIDEO_XXXX
#if defined GC_HAVE_VLC && !defined GC_VIDEO_NONE && !defined GC_VIDEO_QT5
#if !defined GC_VIDEO_VLC
#define GC_VIDEO_VLC
#endif
#endif

// if we aint chosen one or the other then use QT5
#if !defined GC_VIDEO_NONE && !defined GC_VIDEO_QT5 && !defined GC_VIDEO_VLC
#define GC_VIDEO_QT5
#endif

// now check for stupid settings
#if defined GC_VIDEO_QUICKTIME
#error "QuickTime is only supported on Mac OS X"
#endif

#endif // Q_OS_LINUX || Q_OS_WIN

//----------------------------------------------------------------------
// Now options are set lets pull in the headers we need then
//----------------------------------------------------------------------

#ifdef GC_VIDEO_VLC // VLC Video used

// for vlc
#include <stdio.h>
#include <stdlib.h>
#ifndef Q_CC_MSVC
#include <unistd.h>
#else
#define ssize_t SSIZE_T
#endif

extern "C" {
#include <vlc/vlc.h>
#include <vlc/libvlc_media.h>
}

#endif // VLC

#ifdef GC_VIDEO_QT5 // QT5 Video Stuff
#include <QVideoWidget>
#include <QMediaPlayer>
#include <QMediaContent>
#endif

// QT stuff etc
#include <QtGui>
#include <QTimer>
#include "Context.h"
#include "DeviceConfiguration.h"
#include "DeviceTypes.h"
#include "RealtimeData.h"
#include "TrainSidebar.h"

// regardless we always have a media helper
class MediaHelper
{
    public:

        MediaHelper();
        ~MediaHelper();

        // get a list of supported media
        // found in the supplied directory
        QStringList listMedia(QDir directory);
        bool isMedia(QString filename);

    private:
        QStringList supported;
#ifdef GC_VIDEO_VLC
        libvlc_instance_t * inst;
#endif
};

class VideoWindow : public GcChartWindow
{
    Q_OBJECT
    G_OBJECT

    // which layout to use
    Q_PROPERTY(int videoLayout READ videoLayout WRITE setVideoLayout USER true)

    public:

        VideoWindow(Context *);
        ~VideoWindow();
        int videoLayout() const { return layoutSelector ? layoutSelector->currentIndex() : 0; }
        void setVideoLayout(int x) { if (layoutSelector) layoutSelector->setCurrentIndex(x); }


    public slots:

        void layoutChanged();
        void resetLayout();
        void startPlayback();
        void stopPlayback();
        void pausePlayback();
        void resumePlayback();
        void telemetryUpdate(RealtimeData rtd);
        void seekPlayback(long ms);
        void mediaSelected(QString filename);

    protected:

        void resizeEvent(QResizeEvent *);

        // media data

         // Support case where media fps and videosync fps disagree.
        double videoSyncTimeAdjustFactor;

        // Support case where workout distance and videosync distance disagree.
        double videoSyncDistanceAdjustFactor;

        // Adjust time in videosync file point on load.
        VideoSyncFilePoint VideoSyncPointAdjust(const VideoSyncFilePoint& vsfp) const;

        // current data
        int curPosition;
        RideFilePoint rfp;
        float currentVideoRate;

        // passed from Context *
        Context *context;

        bool m_MediaChanged;

        QList<MeterWidget*> m_metersWidget;
        QPoint prevPosition;

    private:
        QList<QString> layoutNames;
        void readVideoLayout(int x, bool useDefault=false);
        void showMeters();

#ifdef GC_VIDEO_VLC

        // vlc for older QT
        libvlc_instance_t * inst;
        //libvlc_exception_t exceptions;
        libvlc_media_player_t *mp;
        libvlc_media_t *m;
#endif

#ifdef GC_VIDEO_QT5
        // QT native
        QMediaContent mc;
        QVideoWidget *wd;
        QMediaPlayer *mp;
#endif

        QWidget *container;
        QComboBox *layoutSelector;
        QPushButton *resetLayoutBtn;

        bool init; // we initialised ok ?
};

#endif // _GC_VideoWindow_h
